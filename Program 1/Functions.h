#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <list>
#include <vector>

#include "SimpleList.h"

void runProgram();

// Takes a line of the text file and splits the words and pushes them into a vector
std::vector<std::string> split(const std::string &s, char delimiter);

// Chooses the list that the command line is requesting
void chooseList(std::vector<std::string> &tokens, std::ofstream &outfile, std::list<SimpleList<int> *> &listInteger, 
std::list<SimpleList<double> *> &listDouble, std::list<SimpleList<std::string> *> &listString);

// Chooses which command to run with respect to the input list
template <typename T>
void chooseCommands(const std::vector<std::string> &tokens, std::ofstream &outfile, std::list<SimpleList<T> *> &lists);

// Chooses to create either stack or queue from the command line
template <typename T>
void create(std::list<SimpleList<T> *> &lists, const std::vector<std::string> &tokens, std::ofstream &outfile) ;

// Creates a queue and pushes it to the list of types
template <typename T>
void createQueue(std::list<SimpleList<T> *> &lists, const std::vector<std::string> &tokens);

// Creates a stack and pushes it to the list of types
template <typename T>
void createStack(std::list<SimpleList<T> *> &lists, const std::vector<std::string> &tokens);

// Takes in the value that's being pushed, finds the list to push to, and pushes it into a stack/queue
template <typename T>
void push(std::list<SimpleList<T> *> &lists, const std::vector<std::string> &tokens, std::ofstream &outfile);

// Pops the top value from the stack/queue to pop from
template <typename T>
void pop(std::list<SimpleList<T> *> &lists, const std::vector<std::string> &tokens, std::ofstream &outfile);

// Checks if the list name exists
template <typename T>
bool checkName(std::list<SimpleList<T> *> &lists, const std::string &name, std::ofstream &outfile);

#endif