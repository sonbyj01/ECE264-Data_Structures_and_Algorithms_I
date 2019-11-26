#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <list>
#include <vector>

#include "SimpleList.h"

void runProgram();

std::vector<std::string> split(const std::string &s, char delimiter);

void chooseList(std::vector<std::string> &tokens, std::ofstream &outfile, std::list<SimpleList<int> *> &listInteger, 
std::list<SimpleList<double> *> &listDouble, std::list<SimpleList<std::string> *> &listString);

template <typename T>
void chooseCommands(const std::vector<std::string> &tokens, std::ofstream &outfile, std::list<SimpleList<T> *> &lists);

template <typename T>
void create(std::list<SimpleList<T> *> &lists, const std::vector<std::string> &tokens, std::ofstream &outfile) ;

template <typename T>
void createQueue(std::list<SimpleList<T> *> &lists, const std::vector<std::string> &tokens);

template <typename T>
void createStack(std::list<SimpleList<T> *> &lists, const std::vector<std::string> &tokens);

template <typename T>
void push(std::list<SimpleList<T> *> &lists, const std::vector<std::string> &tokens, std::ofstream &outfile);

template <typename T>
void pop(std::list<SimpleList<T> *> &lists, const std::vector<std::string> &tokens, std::ofstream &outfile);

template <typename T>
bool checkName(std::list<SimpleList<T> *> &lists, const std::string &name, std::ofstream &outfile);

#endif