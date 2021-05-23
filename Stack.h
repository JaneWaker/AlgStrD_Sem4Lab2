#pragma once
#include <iostream>

template <class T>
class Stack
{
private:
    class Node
    {
    public:
        Node(T data = 0, Node* previous_branch = NULL, Node* next_branch = NULL)
        {
            this->data = data;
            this->previous_branch = previous_branch;
            this->next_branch = next_branch;
        };
        ~Node()
        {  }
        T data;
        Node* previous_branch;
        Node* next_branch;
    private:

    };

    Node* first;
    Node* last;
    size_t size; 

public:
    Stack(Node* first = NULL, Node* last = NULL) {
        this->first = first;
        this->last = last;
        size = 0;
    };
    size_t get_size();
    void push(T); 
    T pop();
    T get_top();
    bool IsEmpty();
    void clear(); 
    ~Stack()
    {
        if (first != NULL) {
            while (first != NULL && first->next_branch != NULL) //while we can go next
            {
                first = first->next_branch;
                delete first->previous_branch;
            }
            size = 0;
            if (first != NULL) delete first;
        }
    };
};
