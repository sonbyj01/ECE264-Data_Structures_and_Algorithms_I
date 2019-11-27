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
        std::string getName();
    name = "";
}

// Sets the head of the list with 'nodeP'
template <typename T>
void SimpleList<T>::setHead(Node *nodeP)
{
    this->head = nodeP;
    return;
}

// Sets the tail of the list with 'nodeP'
template <typename T>
void SimpleList<T>::setTail(Node *nodeP)
{
    this->tail = nodeP;
    return;
}

// Sets the name of the list
template <typename T>
void SimpleList<T>::setName(std::string nameP)
{
    this->name = nameP;
    return;
}

// Returns the name of the list
template <typename T>
std::string SimpleList<T>::getName()
{
    return this->name;
}

// Pops the top of the list
template <typename T>
void SimpleList<T>::pop_value()
{
    if(head == nullptr && tail == nullptr)
    {
        std::cout << "ERROR: This list is empty!" << std::endl;
    }
    if(head == tail){
        head = nullptr;
        tail = nullptr;
    } 
    else 
    {
        Node *temp = this->head;
        this->head = this->head->getNextNode();
        delete temp;
    }
}

// Pushes a node of value 'valueP' to the front of the list
template <typename T>
void SimpleList<T>::push_front(T valueP)
{
    class SimpleList<T>::Node *node = new class SimpleList<T>::Node(valueP);
    if(head == nullptr && tail == nullptr){
        this->setHead(node);
        this->setTail(node);
    }    
    else{
        node->setNextNode(this->head);
        this->setHead(node);
    }
    return;
}

// Pushes a node of value 'valueP' to the end of the list
template <typename T>
void SimpleList<T>::push_back(T valueP)
{
    class SimpleList<T>::Node *node = new class SimpleList<T>::Node(valueP);
    if(head == nullptr && tail == nullptr){
        this->setHead(node);
        this->setTail(node);
    }    
    else{
        this->tail->setNextNode(node);
        this->setTail(node);
    }
}

// Returns false if the stack/queue is empty
template <typename T>
bool SimpleList<T>::checkPop() 
{
    return !(this->head == nullptr && this->tail == nullptr);
}

// Returns the top value of the stack/queue
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

// Pushes the Node value to the front of the Stack
template <typename T>
void Stack<T>::push(T valueP)
{
    this->push_front(valueP);
    return;
}

// Calls the pop function declared in SingleList
template <typename T>
void Stack<T>::pop()
{
    this->pop_value();
    return;
}

// --- Queue ---
template <typename T>
Queue<T>::Queue(std::string nameP)
{
    SimpleList<T>::setHead(nullptr);
    SimpleList<T>::setTail(nullptr);
    SimpleList<T>::setName(nameP);
}

// Pushes the Node value to the back of the Queue
template <typename T>
void Queue<T>::push(T valueP)
{
    this->push_back(valueP);
    return;
}

// Calls the pop function declared in SingleList
template <typename T>
void Queue<T>::pop()
{
    this->pop_value();
    return;
}

#endif