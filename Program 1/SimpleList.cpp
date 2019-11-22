#include "SimpleList.h"

template <typename T>
SimpleList<T>::SimpleList()
{
    head = nullptr;
    tail = nullptr;
    name = "";
}

template <typename T>
std::string SimpleList<T>::getName()
{
    return this->name;
}

template <typename T>
void SimpleList<T>::pop()
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
bool SimpleList<T>::checkPop() 
{
    return !(this->head == nullptr && this->tail == nullptr);
}

template <typename T>
T SimpleList<T>::top()
{
    return this->head->getVaue();
}

// Stack -----------------
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