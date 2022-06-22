#pragma once

#include <iostream>
#include <fstream>
#include "dynamic_array.h"

const int action_table[][3]{
        //L  //N  //R
        {1, 2, 3}, //0
        {4, 5, 6} //1
};


class instructions {
private:
    int length_;
    struct Node {
        int number = -1;
        int action[2] ={-1, -1};
        int next[2] = {-1, -1};
    };
public:
    dynamic_array<Node> instruction;
    explicit instructions(std::ifstream &);
    explicit instructions(int length = 0) :length_(length){};
    instructions &operator=(const instructions&);
    instructions(const instructions &);
    Node get_next_q(int);
    Node get_first_q();
};

int take_num_from_str(const std::string &str, int pstart, int pend);

