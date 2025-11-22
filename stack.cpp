//
// Created by user on 22.11.2025.
//

#include "stack.h"

Stack::Stack() {
    top = new SList;
    length = 0;
}

bool Stack::is_empty() {
    if (length==0) return true;
    return false;
}

void Stack::push(Node *val) {
    if (length==0) {
        top->data=val;
    }else {
        SList* temp = new SList;
        temp->prev = top;
        top = temp;
        top->data=val;
    }
    length++;
}

Node* Stack::pop() {
    Node* temp;
    temp=top->data;
    SList* del = top;
    if (length==0) {
        top=nullptr;
        delete del;
    }
    if (length>1) {

        top = top->prev;
        delete del;
    }
    length--;
    return temp;
}

Node * Stack::peek() {
    if (top!=nullptr)return top->data;
    return nullptr;

}

