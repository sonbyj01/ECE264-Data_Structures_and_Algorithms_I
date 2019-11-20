#include "LinkedList.h"

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