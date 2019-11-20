#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>
#include <vector>
template <typename T>
class Node 
{
    private:
        Node *next;
        T value;
    public:
        // Constructor of a node
        explicit Node(T valueP)
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
class LinkedList
{
    protected:
        Node* head;
        Node* tail;
        string name;
    public:
        LinkedList();
        virtual void push(T value);
        void pop();
        T top();
        std::string getName();
};
#endif