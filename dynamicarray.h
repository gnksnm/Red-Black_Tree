//
// Created by user on 17.11.2025.
//

#ifndef UNTITLED1_DYNAMICARRAY_H
#define UNTITLED1_DYNAMICARRAY_H


class Array {
private:
    int length;
    int *data;
    int binary_search(int searching);
public:
    Array();
    Array(const Array& other);
    ~Array();
    int get_length();
    void pop();
    void add_element(unsigned index, int value);
    void push(int value);
    void push_back(int value);
    int& operator[](unsigned index);
    Array&operator=(const Array& other);
};

#endif //UNTITLED1_DYNAMICARRAY_H