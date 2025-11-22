//
// Created by user on 21.11.2025.
//

#ifndef UNTITLED1_QUEUE_H
#define UNTITLED1_QUEUE_H
#include "Tree.h"
struct List {
    List* next=nullptr;
    List* prev=nullptr;
    Node* data;
};

class Queue {
    List* top;
    List* back;
    unsigned length;
public:
    Queue();
    bool is_empty();
    void in(Node* value);
    Node* out();
};


#endif //UNTITLED1_QUEUE_H