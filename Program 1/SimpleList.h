#ifndef SIMPLELIST_H
#define SIMPLELIST_H

#include <string>

template <typename T>
class SimpleList
{
    private:
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
                void setNextNode(Node *nextNode)
                {
                    this->next = nextNode;
                }
                // Returns (Node) of the next node
                Node* getNextNode()
                {
                    return this->next;
                }
        };
        Node *head;
        Node *tail;
        std::string name;
    protected:
        void push_back(T value);
        void push_front(T value); 
        void pop_value();
        void setHead(Node *head);
        void setTail(Node *tail);
        void setName(std::string name);
    public:
        SimpleList();
        virtual void push(T value) = 0;
        virtual void pop() = 0;
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
        void pop();
};

template <typename T>
class Queue : public SimpleList<T>
{
    public: 
        explicit Queue(std::string name);
        void push(T value);
        void pop();
};

// --- Declarations ---
template <typename T>
SimpleList<T>::SimpleList()
{
    head = nullptr;
    tail = nullptr;
    name = "";
}

template <typename T>
void SimpleList<T>::setHead(Node *nodeP)
{
    this->head = nodeP;
    return;
}

template <typename T>
void SimpleList<T>::setTail(Node *nodeP)
{
    this->tail = nodeP;
    return;
}

template <typename T>
void SimpleList<T>::setName(std::string nameP)
{
    this->name = nameP;
    return;
}

template <typename T>
std::string SimpleList<T>::getName()
{
    return this->name;
}

template <typename T>
void SimpleList<T>::pop_value()
{
    if(head == nullptr && tail == nullptr)
    {
        std::cout << "ERROR: This list is empty!" << std::endl;
    } else 
    {
        Node *temp = this->head;
        this->head = this->head->getNextNode();
        delete temp;
    }
}

template <typename T>
void SimpleList<T>::push_front(T valueP)
{
    std::cout << "41 process" << std::endl;
    class SimpleList<T>::Node *node = new class SimpleList<T>::Node(valueP);
    std::cout << "42 process" << std::endl;
    node->setNextNode(this->head);
    std::cout << "43 process" << std::endl;
    this->head = node;
    std::cout << "44 process" << std::endl;
    return;
}

template <typename T>
void SimpleList<T>::push_back(T valueP)
{
    std::cout << "41 process" << std::endl;
    class SimpleList<T>::Node *node = new class SimpleList<T>::Node(valueP);
    std::cout << "42 process" << std::endl;
    std::cout << node->getValue() << std::endl;
    this->tail->setNextNode(node);
    std::cout << "43 process" << std::endl;
    this->tail = node;
    std::cout << "44 process" << std::endl;
    return;
}

template <typename T>
bool SimpleList<T>::checkPop() 
{
    return !(this->head == nullptr && this->tail == nullptr);
}

template <typename T>
T SimpleList<T>::top()
{
    return this->head->getValue();
}

// --- Stack ---
template <typename T>
Stack<T>::Stack(std::string nameP)
{
    SimpleList<T>::setHead(nullptr);
    SimpleList<T>::setTail(nullptr);
    SimpleList<T>::setName(nameP);
}

template <typename T>
void Stack<T>::push(T valueP)
{
    SimpleList<T>::push_front(valueP);
    return;
}

template <typename T>
void Stack<T>::pop()
{
    SimpleList<T>::pop_value();
    return;
}

// Queue -----------------
template <typename T>
Queue<T>::Queue(std::string nameP)
{
    SimpleList<T>::setHead(nullptr);
    SimpleList<T>::setTail(nullptr);
    SimpleList<T>::setName(nameP);
}

template <typename T>
void Queue<T>::push(T valueP)
{
    SimpleList<T>::push_back(valueP);
    return;
}

template <typename T>
void Queue<T>::pop()
{
    SimpleList<T>::pop_value();
    return;
}

#endif