#include "array.h"

#include <iostream>

Array::Array() : data(nullptr), _size(0) {
}

//Array::~Array() {
//    std::cout << "Delete called on memory address: " << this->data << std::endl;
//    delete[] this->data;
//}

//Array::Array(const Array& other) {
//    this->data = new int[other._size];
//    this->_size = other._size;
//    for (size_t i = 0; i < other._size; ++i) {
//        this->data[i] = other.data[i];
//    }
//}

//Array& Array::operator=(const Array& other) {
//    delete[] this->data;
//    this->data = new int[other._size];
//    this->_size = other._size;
//    for (size_t i = 0; i < other._size; ++i) {
//        this->data[i] = other.data[i];
//    }
//    return *this;
//}

Array Array::operator+(const Array& other) const {
    Array result;
    result._size = this->_size + other._size;
    result.data = new int[result._size];

    // Copy this
    for (size_t i = 0; i < this->_size; i++) {
        result.data[i] = this->data[i];
    }

    // Copy other
    for (size_t i = 0; i < other._size; i++) {
        result.data[i + this->_size] = other.data[i];
    }

    return result;
}

int Array::at(size_t index) const {
    return this->data[index];
}

size_t Array::size() const {
    return this->_size;
}

void Array::push(int value) {
    int* new_data = new int[this->_size + 1];
    for (size_t i = 0; i < this->_size; i++) {
        new_data[i] = data[i];
    }
    new_data[this->_size] = value;
    delete[] this->data;
    this->data = new_data;
    this->_size++;
}
