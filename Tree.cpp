#include "Tree.h"
#include "queue.h"
#include <cctype>
#include <iostream>
#include "stack.h"

// ===================== Tree =====================

Tree::Tree() {
    root = new Node;
    root->data = 0;
    root->left = nullptr;
    root->right = nullptr;
    root->parent = nullptr;
}

void Tree::make_Tree(string str) {

    root = new Node;
    unsigned left_count = 1, right_count = 0;
    unsigned curr = 1;
    Node* temp = root;

    while (curr != str.size()) {
        if (str[curr] == '(') {
            if (temp->left != nullptr) {
                temp->right = new Node;
                temp->right->parent = temp;
                temp = temp->right;
            } else {
                temp->left = new Node;
                temp->left->parent = temp;
                temp = temp->left;
            }
            curr++;
        }
        else if (str[curr] == ')') {
            temp = temp->parent;
            curr++;
        }
        else if (isdigit(str[curr])) {
            int a = str[curr] - '0';
            curr++;
            while (isdigit(str[curr])) {
                a = a * 10 + (str[curr] - '0');
                curr++;
            }
            temp->data = a;
        }
        else if (str[curr] == ' ') {
            curr++;
        }
    }
}

void Tree::direct_traverse(Array* a, Node* node) {
    if (node == nullptr) return;
    node->visit(a);
    direct_traverse(a, node->left);
    direct_traverse(a, node->right);
}

// ===================== Red-Black Tree =====================

void Red_Black::rotate_left(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NIL) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr)
        root = y;
    else if (x->parent->left == x)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void Red_Black::rotate_right(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right != NIL) y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr)
        root = y;
    else if (x->parent->left == x)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->right = x;
    x->parent = y;
}

void Red_Black::insert(int value) {
    Node* z = new Node;
    z->data = value;
    z->left = NIL;
    z->right = NIL;
    Node* x = root;
    Node* y = nullptr;

    while (x != NIL) {
        y = x;
        if (z->data < x->data) x = x->left;
        else x = x->right;
    }

    z->parent = y;
    if (y == nullptr)
        root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;

    fix_insert(z);
}

void Red_Black::fix_insert(Node* z) {
    while (z->parent && z->parent->red) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
            if (y->red) {
                z->parent->red = false;
                y->red = false;
                z->parent->parent->red = true;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rotate_left(z);
                }
                z->parent->red = false;
                z->parent->parent->red = true;
                rotate_right(z->parent->parent);
            }
        } else {
            Node* y = z->parent->parent->left;
            if (y->red) {
                z->parent->red = false;
                y->red = false;
                z->parent->parent->red = true;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rotate_right(z);
                }
                z->parent->red = false;
                z->parent->parent->red = true;
                rotate_left(z->parent->parent);
            }
        }
    }
    root->red = false;
}

Node* Red_Black::minimum(Node* x) {
    while (x->left != NIL)
        x = x->left;
    return x;
}

Red_Black::Red_Black() : Tree() {
    NIL = new Node;
    NIL->red = false;
    root=NIL;
}

Node * Red_Black::find_el(int data) {
    Node* z = root;
    while (z != nullptr && z->data != data) {
        if (data < z->data) z = z->left;
        else z = z->right;
    }
    if (z == nullptr) return nullptr;
    return z;
}

void Red_Black::make_Tree(string str) {
    Tree temp;
    temp.make_Tree(str);
    Array a;
    temp.direct_traverse(&a, temp.get_root());

    //root->data = a[0];
    root->left = root->right =root->parent= NIL;
    //a.pop();

    for (int i = 0; i < a.get_length(); i++) {
        insert(a[i]);
    }
}

void Red_Black::transplant(Node* u, Node* v) {
    if (u->parent == nullptr)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (v != nullptr)
        v->parent = u->parent;
}

void Red_Black::delete_node(int data) {
    Node* z = root;
    // поиск удаляемого узла
    while (z != nullptr && z->data != data) {
        if (data < z->data) z = z->left;
        else z = z->right;
    }
    if (z == nullptr) return; // нет узла

    Node* y = z;
    Node* x = NIL;
    bool y_original_color = y->red;

    if (z->left == nullptr) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == nullptr) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = minimum(z->right);
        y_original_color = y->red;
        x = y->right;
        if (y->parent == z) {
            if (x) x->parent = y;
        } else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->red = z->red;
    }
    delete z;
    if (!y_original_color) fix_delete(x);
}

void Red_Black::fix_delete(Node* x) {
    while (x == NIL && !x->red && x != root) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;
            if (w->red) {
                w->red = false;
                x->parent->red = true;
                rotate_left(x->parent);
                w = x->parent->right;
            }
            if ((w->left == nullptr || !w->left->red) && (w->right == nullptr || !w->right->red)) {
                w->red = true;
                x = x->parent;
            } else {
                if (w->right == nullptr || !w->right->red) {
                    if (w->left) w->left->red = false;
                    w->red = true;
                    rotate_right(w);
                    w = x->parent->right;
                }
                w->red = x->parent->red;
                x->parent->red = false;
                if (w->right) w->right->red = false;
                rotate_left(x->parent);
                x = root;
            }
        } else {
            Node* w = x->parent->left;
            if (w->red) {
                w->red = false;
                x->parent->red = true;
                rotate_right(x->parent);
                w = x->parent->left;
            }
            if ((w->left == nullptr || !w->left->red) && (w->right == nullptr || !w->right->red)) {
                w->red = true;
                x = x->parent;
            } else {
                if (w->left == nullptr || !w->left->red) {
                    if (w->right) w->right->red = false;
                    w->red = true;
                    rotate_left(w);
                    w = x->parent->left;
                }
                w->red = x->parent->red;
                x->parent->red = false;
                if (w->left) w->left->red = false;
                rotate_right(x->parent);
                x = root;
            }
        }
    }
    if (x) x->red = false;
}

// ===================== Traversals =====================

Array Red_Black::direct_traverse() {
    Array a;
    Stack stack;
    Node* node = root;
    stack.push(node);

    while (!stack.is_empty()) {
        Node* curr = stack.pop();
        if (curr != NIL) curr->visit(&a);
        if (curr->right != NIL) stack.push(curr->right);
        if (curr->left != NIL) stack.push(curr->left);
    }
    return a;
}

Array Red_Black::centered_traverse() {
    Array a;
    Stack stack;
    Node* node = root;

    while (!(stack.is_empty()) || node != NIL) {
        if (node != NIL) {
            stack.push(node);
            node = node->left;
        } else {
            node = stack.pop();
            if (node != NIL) node->visit(&a);
            node = node->right;
        }
    }
    return a;
}

Array Red_Black::reverse_traverse() {
    Array a;
    Stack stack;
    Node* node = root;
    Node* last_visited = nullptr;

    while (!(stack.is_empty()) || (node != NIL)) {
        if (last_visited == root) break;

        if (node != NIL && node != last_visited) {
            stack.push(node);
            node = node->left;
        } else {
            node = stack.peek();
            if (node->right != NIL && last_visited != node->right) {
                node = node->right;
            } else {
                if (node != NIL) node->visit(&a);
                last_visited = node;
                stack.pop();
            }
        }
    }
    return a;
}

Array Red_Black::width_traverse() {
    Array a;
    Queue queue;
    Node* node = root;
    Node* curr;
    queue.in(node);

    while (!queue.is_empty()) {
        curr = queue.out();
        if (curr != NIL) curr->visit(&a);
        if (curr->left != NIL) queue.in(curr->left);
        if (curr->right != NIL) queue.in(curr->right);
    }
    return a;
}
