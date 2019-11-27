#include <fstream>
#include <sstream>
#include <iostream>

#include "Functions.h"

int main() 
{
    runProgram();
    return 0;
}

// --- Implementations of functions ---
void runProgram()
{
    // Input and Output files
    std::string inputFile;
    std::string outputFile;

    // Lists of SimpleList of types
    std::list<SimpleList<int> *> listInteger;
    std::list<SimpleList<double> *> listDouble;
    std::list<SimpleList<std::string> *> listString;

    std::cout << "Input file: " << std::endl;
    std::cin >> inputFile;
    std::cout << "Output file: " << std::endl;
    std::cin >> outputFile;

    std::ifstream infile(inputFile);
    std::ofstream outfile(outputFile);

    if(infile)
    {
        std::string commands;
        while(getline(infile, commands))
        {
            std::vector<std::string> tokens = split(commands, ' ');
            outfile << "PROCESSING COMMAND: " << commands << std::endl;
            chooseList(tokens, outfile, listInteger, listDouble, listString);
        }
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

void chooseList(std::vector<std::string> &tokens, std::ofstream &outfile, std::list<SimpleList<int> *> &listInteger, 
std::list<SimpleList<double> *> &listDouble, std::list<SimpleList<std::string> *> &listString)
{
    char type = tokens[1][0];
    if(type == 'i')
    {
        chooseCommands(tokens, outfile, listInteger);
    } else if(type == 'd')
    {
        chooseCommands(tokens, outfile, listDouble);
    } else
    {
        chooseCommands(tokens, outfile, listString);
    }
    
    return;
}

template <typename T>
void chooseCommands(const std::vector<std::string> &tokens, std::ofstream &outfile, std::list<SimpleList<T> *> &lists)
{
    std::string command = tokens[0];
    if(command == "create")
    {
        create(lists, tokens, outfile);
    } else if(command == "push")
    {
        push(lists, tokens, outfile);
    } else if(command == "pop")
    {
        pop(lists, tokens, outfile);
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
    std::string listType = tokens[2];
    if (listType == "queue") {
        createQueue(lists, tokens);
    } else if (listType == "stack") {
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
    for(auto const& list : lists)
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
            } else
            {
                outfile << "Value popped: " << list->top() << std::endl;
                list->pop();
            }
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