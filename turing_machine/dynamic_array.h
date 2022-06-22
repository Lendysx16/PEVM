#pragma once

#include <iostream>
#include "quicksort.h"

#ifndef Dynamic_array_T
#define Dynamic_array_T


template<typename T>
class dynamic_array {
private:
    bool sorted = false;
    size_t size_;
    size_t elements_used_ = 0;
    T *arr_ = nullptr;
public:
    explicit dynamic_array(size_t X = 1) : size_(X + 1) {
        arr_ = new T[size_];
    }
    dynamic_array(const dynamic_array<T> &X);

    dynamic_array(dynamic_array<T> &&X) noexcept;

    void sort() {
        if (!sorted) {
            quicksort(arr_, 0, elements_used_ - 1);
            sorted = true;
        }
    }

    size_t get_elements_used() { return elements_used_; }

    void append(const T &X);

    void pop(int i = 1) {
        elements_used_ -= i;
    }

    friend void print(const dynamic_array<T> &X){
            if (X.elements_used_ != 0) {
                std::cout << "[";
                for (auto i = 0; i < X.elements_used_ - 1; ++i) {
                    std::cout << X.arr_[i] << ", ";
                }
                std::cout << X.arr_[X.elements_used_ - 1] << "]" << std::endl;
            } else {
                std::cout << "[]" << std::endl;
            }

    }

    T &operator[](int i) {
        if (i > size_ or size_ == 0) {
            throw std::invalid_argument("Out of range " + std::to_string(i));
        }
        return arr_[i];
    }

    ~dynamic_array() {
        delete[] arr_;
    }

    dynamic_array<T> &operator=(const dynamic_array<T> &X);
    dynamic_array<T> &operator=(dynamic_array<T> &&X) noexcept;
};

template<typename T>
dynamic_array<T> &dynamic_array<T>::operator=(dynamic_array<T> &&X) noexcept {
    if (this != &X) {
        delete arr_;
        arr_ = X.arr_;
        size_ = X.size_;
        elements_used_ = X.elements_used_;
        X.size_ = 0;
        X.elements_used_ = 0;
        X.arr_ = nullptr;
    }
    return *this;
}


template<typename T>
dynamic_array<T> &dynamic_array<T>::operator=(const dynamic_array<T> &X) {
    if (this != &X) {
        delete arr_;
        arr_ = new T[X.size_];
        size_ = X.size_;
        elements_used_ = X.elements_used_;
        for (int i = 0; i < elements_used_; ++i) arr_[i] = X.arr_[i];
    }
    return *this;
}

template<typename T>
void dynamic_array<T>::append(const T &X) {
    sorted = false;
    if (elements_used_ > size_ - 1) {
        auto tmp = new T[size_ * 2];
        for (auto i = 0; i < elements_used_; ++i) tmp[i] = arr_[i];
        size_ *= 2;
        delete[] arr_;
        arr_ = tmp;
    }
    arr_[elements_used_] = X;
    ++elements_used_;
}

template<typename T>
dynamic_array<T>::dynamic_array(dynamic_array<T> &&X) noexcept {
    delete arr_;
    arr_ = X.arr_;
    size_ = X.size_;
    elements_used_ = X.elements_used_;
    X.size_ = 0;
    X.elements_used_ = 0;
    X.arr_ = nullptr;
}

template<typename T>
dynamic_array<T>::dynamic_array(const dynamic_array<T> &X) {
    delete arr_;
    arr_ = new T[X.size_];
    size_ = X.size_;
    elements_used_ = X.elements_used_;
    for (int i = 0; i < elements_used_; ++i) arr_[i] = X.arr_[i];
}

#endif

