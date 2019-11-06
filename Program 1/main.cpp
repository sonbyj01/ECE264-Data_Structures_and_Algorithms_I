#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> 
using namespace std;

void readFile(ifstream& infile, ofstream& outfile);
vector<string> split(const string &s, char delimiter);

/*
 * Function that reads the input file line-by-line, sends to output file, and runs the commands 
 * Returns: nothing
 */
void readFile(ifstream& infile, ofstream& outfile)
{
    if(infile)
    {
        string commands;
        while(getline(infile, commands))
        {
            vector<string> tokens = split(commands, ' ');
            outfile << "PROCESSING COMMAND: " << commands << endl;
            runCommands()
        }
        infile.close();
    } else 
    {
        cout << "File cannot be opened" << endl;
    }
    return;
}

/*
 * Function that splits a line of commands and puts it into a vector
 * Returns: a vector string that contains tokens of commands
 */
vector<string> split(const string &s, char delimiter)
{
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while(getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

int main() 
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
    return 0;
}