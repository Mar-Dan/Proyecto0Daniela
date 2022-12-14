#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H
#define DEFAULT_MAX_SIZE 1024
#include "Stack.h"
#include <iostream>
#include <stdexcept>

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class ArrayStack : public Stack<E>{
private:
    E *elements;
    int top;
    int max;

public:
    ArrayStack(int max = DEFAULT_MAX_SIZE){
        elements = new E[max];
        top=0;
        this->max = max;
    }
    ~ArrayStack(){
        delete [] elements;
    }
    void push(E element){
        if (top==max)
            throw runtime_error("Stack overflow.");
        elements[top]=element;
        top++;
    }
    E pop(){
        if(top==0)
            throw runtime_error("Stack underflow.");
        top--;
        return elements[top];
    }
    E topValue(){
        if(top==0)
            throw runtime_error("Stack is empty.");
        return elements[top-1];
    }
    void clear(){
        top = 0;
    }
    bool isEmpty(){
        return top==0;
    }
    int getSize(){
        return top;
    }
    void print(){
        cout<<"{ ";
        for (int i = top-1; i>=0; i++)
            cout<<elements[i]<<" ";
        cout<<"}"<<endl;
    }

};

#endif // ARRAYSTACK_H
