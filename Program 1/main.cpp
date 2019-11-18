#include "Functions.h"
#include "LinkedList.h"
using namespace std;

void main() 
{
    runProgram();
    return;
}

// --- IMPLEMENTATIONS OF 'Functions.h' ---
void runProgram()
{
    string inputFile;
    string outputFile;

    cout << "Input file: " << endl;
    cin >> inputFile;
    cout << "Output file: " << endl;
    cin >> outputFile;

    ifstream infile(inputFile);
    ofstream outfile(outputFile);

    readFile(infile, outfile);
    return;
}

void readFile(ifstream& infile, ofstream& outfile)
{
    if(infile)
    {
        string commands;
        while(getline(infile, commands))
        {
            vector<string> tokens = split(commands, ' ');
            outfile << "PROCESSING COMMAND: " << commands << endl;
            runCommands(tokens);
        };
        infile.close();
    } else 
    {
        cout << "File cannot be opened." << endl;
    }
    return;
}

vector<string> split(const string &s, char delimiter)
{
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while(getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    };
    return tokens;
}

template <typename T>
void runCommands(vector<string> tokens)
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
void create(list<LinkedList<T> *> &lists, const vector<std::string> &commands, ofstream &outfile) 
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
}