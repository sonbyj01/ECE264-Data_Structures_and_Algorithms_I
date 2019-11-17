#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>

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

template <typename T>
LinkedList<T>::LinkedList()
{
    head = nullptr;
    tail = nullptr;
    name = "";
}

template <typename T>
std::string LinkedList<T>::getName()
{
    return this->name;
}

template <typename T>
void LinkedList<T>::pop()
{
    if(head == nullptr && tail == nullptr)
    {
        cout << "ERROR: This list is empty!" << endl;
    } else 
    {
        Node *temp = this->head;
        this->head = this->head->getNextNode();
        delete temp;
    }
}

template <typename T>
T LinkedList<T>::top()
{
    return this->head->getVaue();
}

// Stack -----------------
template <typename T>
class Stack : public LinkedList<T>
{
    explicit Stack(std::string nameP);
    void push(T value);
};

template <typename T>
Stack<T>::Stack(std::string nameP)
{
    this->head = nullptr;
    this->tail = nullptr;
    this->name = nameP;
}

template <typename T>
void Stack<T>::push(T valueP)
{
    Node *node = new class Node(valueP);
    node->setNextNode(this->head);
    this->head = node;
    return;
}

// Queue -----------------
template <typename T>
class Queue : public LinkedList<T>
{
    explicit Queue(std::string nameP);
    void push(T value);
};

template <typename T>
Queue<T>::Queue(std::string nameP)
{
    this->head = nullptr;
    this->tail = nullptr;
    this->name = nameP;
}

template <typename T>
void Stack<T>::push(T valueP)
{
    Node *node = new class Node(valueP);
    this->tail->setNextNode(node);
    this->tail = node;
    return;
}
#endif