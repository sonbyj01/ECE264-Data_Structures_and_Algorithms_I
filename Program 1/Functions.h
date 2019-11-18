#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <list>

#include "LinkedList.h"

/*
 * Function that runs the entire program
 * Returns: nothing
 */
void runProgram();

/*
 * Function that reads the input file line-by-line, sends to output file, and runs the commands 
 * Returns: nothing
 */
void readFile(std::ifstream& infile, std::ofstream& outfile);

/*
 * Function that processes the commands within one line
 * Returns: nothing
 */
void runCommands(std::vector<std::string> tokens);

/*
 * Function that splits a line of commands and puts it into a vector
 * Returns: a vector string that contains tokens of commands
 */
std::vector<std::string> split(const std::string &s, char delimiter);

/*
 * Function that chooses which list the line of command applies to
 * Returns: nothing
 */
void chooseList(std::list<LinkedList<int> *> &listSLi, std::list<LinkedList<double> *> &listSLd, 
std::list<LinkedList<std::string> *> &listSLs, const std::vector<std::string> &commands, std::ofstream &outfile);

/*
 * Function that processes the commands within one line
 * Returns: nothing
 */
template <typename T>
void parseCommand(std::list<LinkedList<T> *> &list, const std::vector<std::string> &commands, std::ofstream &outfile);

/*
 * Function that chooses which list the line of command applies to
 * Returns: nothing
 */
template <typename T>
void create(std::list<LinkedList<T> *> &list, const std::vector<std::string> &commands, std::ofstream &outfile);

/*
 * Function that chooses which list the line of command applies to
 * Returns: nothing
 */
template<class T>
void create_queue(std::list<LinkedList<T> *> &lists, const std::vector<std::string> &commands);

/*
 * Function that chooses which list the line of command applies to
 * Returns: nothing
 */
template<class T>
void create_stack(std::list<LinkedList<T> *> &lists, const std::vector<std::string> &commands);

/*
 * Function that chooses which list the line of command applies to
 * Returns: nothing
 */
template<class T>
void pop(std::list<LinkedList<T> *> &lists, const std::vector<std::string> &commands, std::ofstream &outfile);

/*
 * Function that chooses which list the line of command applies to
 * Returns: nothing
 */
template<class T>
void push(std::list<LinkedList<T> *> &lists, const std::vector<std::string> &commands, std::ofstream &outfile);

/*
 * Function that chooses which list the line of command applies to
 * Returns: nothing
 */
template<class T>
bool check_existence(std::list<LinkedList<T> *> &lists, const std::string &name, std::ofstream &outfile);

#endif FUNCTIONS_H