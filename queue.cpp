//
// Created by user on 21.11.2025.
//

#include "queue.h"

Queue::Queue() {
    top = nullptr;
    back = nullptr;
    length = 0;
}

bool Queue::is_empty() {
    if (length>0) return false;
    else return true;
}

void Queue::in(Node* value) {
    List* curr= new List;
    if (length == 0) {
        back=top=curr;
    }
    else {
        curr->next = back;
        back->prev = curr;
        back=curr;
    }
    back->data=value;
    length++;
}

Node* Queue::out() {
    List* del = top;
    Node* value = top->data;
    if (length==1) {
        top=back=nullptr;
    }else{
        top = top->prev;
        top->next = nullptr;
    } delete del;
    length--;
    return value;
}



