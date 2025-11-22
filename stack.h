//
// Created by user on 22.11.2025.
//

#ifndef UNTITLED1_STACK_H
#define UNTITLED1_STACK_H
#include "Tree.h"

struct SList {
    SList* prev=nullptr;
    Node* data;

};

class Stack {
    SList* top;
    unsigned length;
public:
    Stack();
    bool is_empty();
    void push(Node* val);
    Node* pop();
    Node* peek();
};


#endif //UNTITLED1_STACK_H