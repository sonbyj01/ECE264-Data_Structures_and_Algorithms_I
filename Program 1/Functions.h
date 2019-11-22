#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <fstream>
#include <sstream>
#include <list>

#include "SimpleList.h"

/*
 * Function that runs the entire program
 * Returns: nothing
 */
void runProgram();

/*
 * Function that reads the input file line-by-line, sends to output file, and runs the commands 
 * Returns: nothing
 */
void readFile(std::ifstream& infile, std::ofstream &outfile, std::list<SimpleList<int> *> &listInteger, 
std::list<SimpleList<double> *> &listDouble, std::list<SimpleList<std::string> *> &listString);

/*
 * Function that splits a line of commands and puts it into a vector
 * Returns: a vector string that contains tokens of commands
 */
std::vector<std::string> split(const std::string &s, char delimiter);

void runCommand(std::vector<std::string> tokens, std::ofstream &outfile, std::list<SimpleList<int> *> &listInteger, 
std::list<SimpleList<double> *> &listDouble, std::list<SimpleList<std::string> *> &listString);

template <typename T>
SimpleList<T> chooseList(std::vector<std::string> tokens, std::list<SimpleList<int> *> &listInteger, 
std::list<SimpleList<double> *> &listDouble, std::list<SimpleList<std::string> *> &listString);

template <typename T>
void create(std::list<SimpleList<T> *> &lists, const std::vector<std::string> &tokens, std::ofstream &outfile);

template <typename T>
void create_queue(std::list<SimpleList<T> *> &lists, const std::vector<std::string> &tokens);

template <typename T>
void create_stack(std::list<SimpleList<T> *> &lists, const std::vector<std::string> &tokens);

template <typename T>
void push(std::list<SimpleList<T> *> &lists, const std::vector<std::string> &tokens, std::ofstream &outfile);

template <typename T>
void pop(std::list<SimpleList<T> *> &lists, const std::vector<std::string> &tokens, std::ofstream &outfile);

template <typename T>
bool checkName(std::list<SimpleList<T> *> &lists, const std::string &name, std::ofstream &outfile);
#endif