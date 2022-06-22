#pragma once

#include <iostream>
#include "instructions.h"
#include "lenta.h"


class turing_machine {
private:
    instructions inst;
    Lenta lent;
public:
    turing_machine(int length, const instructions &X) : lent(length), inst(X) {};

    turing_machine(const turing_machine &X) {
        inst = X.inst;
        lent = X.lent;
    };

    turing_machine &operator=(const turing_machine &X) {
        if (this != &X) {
            inst = X.inst;
            lent = X.lent;
        }
        return *this;
    }

    std::string calc(const std::string &init, int maxsteps);
};


int take_num_from_str(const std::string &, int, int);