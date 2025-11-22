//
// Created by user on 17.11.2025.
//

#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H
#include "dynamicarray.h"
#include <string>
#include <iostream>
using namespace std;

struct Node {
    Node* parent=nullptr;
    Node* right=nullptr;
    Node* left=nullptr;
    bool red = true;
    int data;
    void visit(Array* a) {
        a->push_back(data);
    }
};

class Tree {
protected:
    Node* root;
private:
    void is_number(char token);
public:
    Tree();
    Node* get_root() {
        return root;
    }
    virtual void make_Tree(string str);
    //~Tree();
    void direct_traverse(Array* a,Node* node);
};

class Red_Black: public Tree {
private:
    Node* NIL;
    void rotate_left(Node* x);
    void rotate_right(Node* x);
    bool is_balance();
    void insert(int value);
    void fix_insert(Node* z);
    Node* minimum(Node* x);
public:
    Red_Black();
    void make_Tree(string str) override;
    void transplant(Node* u, Node* v);
    void delete_node(int data);
    void fix_delete(Node* x);
    Array direct_traverse();
    Array centered_traverse();
    Array reverse_traverse();
    Array width_traverse();

};



#endif //UNTITLED1_TREE_H
