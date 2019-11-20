#include "Functions.h"
#include "LinkedList.h"
template <typename T>
void runProgram()
{
    std::string inputFile;
    std::string outputFile;
    std::list<LinkedList *> masterList;

    std::cout << "Input file: " << std::endl;
    std::cin >> inputFile;
    std::cout << "Output file: " << std::endl;
    std::cin >> outputFile;

    std::ifstream infile(inputFile);
    std::ofstream outfile(outputFile);

    readFile(infile, outfile, masterList);
    return;
}

template <typename T>
void readFile(std::ifstream& infile, std::ofstream& outfile, std::list<LinkedList<T> *> &masterList)
{
    if(infile)
    {
        std::string commands;
        while(getline(infile, commands))
        {
            std::vector<std::string> tokens = split(commands, ' ');
            outfile << "PROCESSING COMMAND: " << commands << std::endl;
            runCommands(tokens, masterList);
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

template <typename T>
void runCommands(std::vector<std::string> tokens, std::list<LinkedList<T> *> &masterList)
{
    if(tokens[0] == "create")
    {
        create(tokens);
    } else if(tokens[0] == "push")
    {
        push(tokens);
    } else if(tokens[0] == "pop")
    {
        pop(tokens);
    }
    return;
}

template <typename T>
void create(std::list<LinkedList<T> *> &lists, const std::vector<std::string> &commands, std::ofstream &outfile) 
{
    for (LinkedList<T> *list: lists) 
    {
        if (list->getName() == commands[1]) 
        {
            outfile << "ERROR: This name already exists!" << std::endl;
            return;
        }
    }
    if (commands[2] == "queue") {
        create_queue(lists, commands);
    } else if (commands[2] == "stack") {
        create_stack(lists, commands);
    }
    return;
}

template <typename T>
void create_queue(std::list<LinkedList<T> *> &lists, const std::vector<std::string> &commands)
{
    
    return;
}