//
// Created by Thomas Morrison on 3/22/26.
//

#ifndef UNTITLED4_ARRAYSTACK_H
#define UNTITLED4_ARRAYSTACK_H

#include <vector>
#include <stdexcept>

template <typename T>
class ArrayStack {
    private: std::vector<T> data;
    public: void push(const T& item) {
        data.push_back(item);
    }
    void pop() {
        if (data.empty()) throw std::runtime_error("Stack is empty");
        data.pop_back();
    }
    T top() const {
        if (data.empty()) throw std::runtime_error("Stack is empty");
        return data.back();
    }
    bool empty() const {
        return data.empty();
    }
    int size() const {
        return data.size();
    }
};

#endif //UNTITLED4_ARRAYSTACK_H



