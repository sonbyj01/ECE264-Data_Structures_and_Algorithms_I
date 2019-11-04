#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() 
{
    string inputFile;
    string outputFile;
    cout << "Input file: ";
    getline(cin,inputFile);
    cout << inputFile << endl;
    cout << "Output file: ";
    getline(cin, outputFile);
    cout << outputFile << endl;

}