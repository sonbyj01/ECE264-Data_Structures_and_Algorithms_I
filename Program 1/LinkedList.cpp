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
        std::cout << "ERROR: This list is empty!" << std::endl;
    } else 
    {
        Node<T> *temp = this->head;
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
    Node<T> *node = new class Node<T>(valueP);
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
void Queue<T>::push(T valueP)
{
    Node<T> *node = new class Node<T>(valueP);
    this->tail->setNextNode(node);
    this->tail = node;
    return;
}