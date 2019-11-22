#include "Functions.h"
#include "SimpleList.h"
void runProgram()
{
    std::string inputFile;
    std::string outputFile;

    std::list<SimpleList<int> *> listInteger;
    std::list<SimpleList<double> *> listDouble;
    std::list<SimpleList<std::string> *> listString;

    std::cout << "Input file: " << std::endl;
    std::cin >> inputFile;
    std::cout << "Output file: " << std::endl;
    std::cin >> outputFile;

    std::ifstream infile(inputFile);
    std::ofstream outfile(outputFile);

    readFile(infile, outfile, listInteger, listDouble, listString);
    return;
}

void readFile(std::ifstream& infile, std::ofstream &outfile, std::list<SimpleList<int> *> &listInteger, 
std::list<SimpleList<double> *> &listDouble, std::list<SimpleList<std::string> *> &listString)
{
    if(infile)
    {
        std::string commands;
        while(getline(infile, commands))
        {
            std::vector<std::string> tokens = split(commands, ' ');
            outfile << "PROCESSING COMMAND: " << commands << std::endl;
            runCommand(tokens, outfile, listInteger, listDouble, listString);
        };
        infile.close();
    } else 
    {
        std::cout << "File cannot be opened." << std::endl;
    }
    return;
}

std::vector<std::string> split(const std::string &s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while(getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    };
    return tokens;
}

void runCommand(std::vector<std::string> tokens, std::ofstream &outfile, std::list<SimpleList<int> *> &listInteger, 
std::list<SimpleList<double> *> &listDouble, std::list<SimpleList<std::string> *> &listString)
{
    if(tokens[0] == "create")
    {
        create(chooseList(tokens, listInteger, listDouble, listString), tokens, outfile);
    } else if(tokens[0] == "push")
    {
        push(chooseList(tokens, listInteger, listDouble, listString), tokens, outfile);
    } else if(tokens[0] == "pop")
    {
        pop(chooseList(tokens, listInteger, listDouble, listString), tokens, outfile);
    }
    return;
}

template <typename T>
SimpleList<T> chooseList(std::vector<std::string> tokens, std::list<SimpleList<int> *> &listInteger, 
std::list<SimpleList<double> *> &listDouble, std::list<SimpleList<std::string> *> &listString)
{
    char type = tokens[1][0];
    if(type == 'i')
    {
        return listInteger;
    } else if(type == 'd')
    {
        return listDouble;
    } else
    {
        return listString;
    }
}

template <typename T>
void create(std::list<SimpleList<T> *> &lists, const std::vector<std::string> &tokens, std::ofstream &outfile) 
{
    for (SimpleList<T> *list:lists) 
    {
        if (list->getName() == tokens[1]) 
        {
            outfile << "ERROR: This name already exists!" << std::endl;
            return;
        }
    }
    if (tokens[2] == "queue") {
        createQueue(lists, tokens);
    } else if (tokens[2] == "stack") {
        createStack(lists, tokens);
    }
    return;
}

template <typename T>
void createQueue(std::list<SimpleList<T> *> &lists, const std::vector<std::string> &tokens)
{
    Queue<T> *var = new class Queue<T>(tokens[1]);
    lists.push_front(var);
    return;
}

template <typename T>
void createStack(std::list<SimpleList<T> *> &lists, const std::vector<std::string> &tokens)
{
    Stack<T> *var = new class Stack<T>(tokens[1]);
    lists.push_front(var);
    return;
}

template <typename T>
void push(std::list<SimpleList<T> *> &lists, const std::vector<std::string> &tokens, std::ofstream &outfile)
{
    if(!checkName(lists, tokens[1], outfile))
    {
        return;
    }
    for(SimpleList<T> *list:lists)
    {
        if(list->getName() == tokens[1])
        {
            std::stringstream ss(tokens[2]);
            T val;
            ss >> val;
            list->push(val);
        }
    }
    return;
}

template <typename T>
void pop(std::list<SimpleList<T> *> &lists, const std::vector<std::string> &tokens, std::ofstream &outfile)
{
    if(!checkName(lists, tokens[1], outfile))
    {
        return;
    }
    for(SimpleList<T> *list:lists)
    {
        if(list->getName() == tokens[1])
        {
            if(!list->checkPop())
            {
                outfile << "ERROR: This list is empty!" << std::endl;
            }
            outfile << "Value popped: " << list->top() << std::endl;
            list->pop();
        }
    }
    return;
}

template <typename T>
bool checkName(std::list<SimpleList<T> *> &lists, const std::string &name, std::ofstream &outfile)
{
    for(SimpleList<T> *list: lists)
    {
        if(list->getName() == name)
        {
            return true;
        }
    }
    outfile << "ERROR: This name does not exist!" << std::endl;
    return false;
}