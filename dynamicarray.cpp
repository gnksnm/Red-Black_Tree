//
// Created by user on 17.11.2025.
//

#include "dynamicarray.h"
#include <stdexcept>

Array::Array() {
    length = 0;
    data = new int[length];
}
Array::Array(const Array &other) {
    length = other.length;
    if (length > 0) {
        data = new int[length];
        for (unsigned i = 0; i < length; ++i)
            data[i] = other.data[i];
    } else {
        data = nullptr;
    }
}

Array::~Array() {
    delete[] data;
}

int Array::get_length() {
    return length;
}

void Array::pop() {
    int* a = new int[length-1];
    for (int i =0; i<length-1;i++) {
        a[i]=data[i+1];
    }
    data=a;
    length--;
}

void Array::add_element(unsigned index, int value) {
    if (index > length) {
        throw std::out_of_range("Index out of range");
    }
    int* arr = new int[length + 1];

    for (unsigned i = 0; i < index; i++){
        arr[i] = data[i];
    }
    arr[index] = value;

    for (unsigned i = index; i < length; i++) {
        arr[i + 1] = data[i];
    }
    delete[] data;
    data = arr;
    ++length;
}

void Array::push(int value) {
    this->add_element(0,value);

}

void Array::push_back(int value) {
    this->add_element(length,value);
}

int& Array::operator[](unsigned index) {
    if (index >= length)
        throw std::out_of_range("Index out of range!");
    return data[index];
}

Array & Array::operator=(const Array &other) {
    if (this == &other)
        return *this;

    delete[] data;
    length = other.length;
    if (length > 0) {
        data = new int[length];
        for (unsigned i = 0; i < length; ++i)
            data[i] = other.data[i];
    } else {
        data = nullptr;
    }
    return *this;
}
