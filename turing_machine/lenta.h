#pragma once

#include <iostream>
#include <fstream>
#include "dynamic_array.h"


class Lenta{
private:
int length_;
public:
    dynamic_array<int> sequence_;
    explicit Lenta(int length = 0);
    Lenta(const Lenta&);
    Lenta &operator=(const Lenta&);
    int &operator[](int);
    int get_len() const {return length_;};
};



