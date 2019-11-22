#ifndef SIMPLELIST_H
#define SIMPLELIST_H

#include <string>
#include <vector>
#include <iostream>

template <typename T>
class Node 
{
    private:
        Node<T> *next;
        T value;
    public:
        // Constructor of a node
        Node(T valueP)
        {
            next = nullptr;
            value = valueP;
        }
        // Returns (T) of the value of current node value
        T getValue()
        {
            return this->value;
        }
        // Sets the address of the next node
        void setNextNode(Node *newNextNode)
        {
            next = newNextNode;
        }
        // Returns (Node) of the next node
        Node* getNextNode()
        {
            return this->next;
        }
};

template <typename T>
class SimpleList
{
    protected:
        Node<T> *head;
        Node<T> *tail;
        std::string name;
    public:
        SimpleList();
        virtual void push(T value);
        void pop();
        bool checkPop();
        T top();
        std::string getName();
};

template <typename T>
class Stack : public SimpleList<T>
{
    public: 
        explicit Stack(std::string name);
        void push(T value);
};

template <typename T>
class Queue : public SimpleList<T>
{
    public: 
        explicit Queue(std::string name);
        void push(T value);
};
#endif