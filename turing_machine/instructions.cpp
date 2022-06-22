#include "instructions.h"


instructions::instructions(std::ifstream &X) {
    std::string str;
    length_ = 0;
    while (getline(X, str)) {
        Node tmp;
        int i = 1;
        int j = 1;
        while (str[j] != ' ')++j;
        tmp.number = take_num_from_str(str, i, j);
        while (str[j] == ' ') ++j;
        i = j + 1;
        int start_bool = int(str[j] - '0');
        while (not(str[i] >= '0' and str[i] <= '9')) ++i;
        j = i;
        while (str[j] != ' ') ++j;
        if (start_bool) {
            tmp.next[1] = take_num_from_str(str, i, j);
        } else {
            tmp.next[0] = take_num_from_str(str, i, j);
        }
        i = j + 1;
        j += 2;
        auto action_num = take_num_from_str(str, i, j);
        auto action_ch = str[j + 1];
        switch (action_ch) {
            case 'L': {
                tmp.action[static_cast<int>(start_bool)] = action_table[action_num][0];
                break;
            }
            case 'N': {
                tmp.action[static_cast<int>(start_bool)] = action_table[action_num][1];
                break;
            }
            case 'R': {
                tmp.action[static_cast<int>(start_bool)] = action_table[action_num][2];
                break;
            }
            default: {
                throw std::invalid_argument(str);
            }
        }
        int tmp_in_arr = -1;
        for (int k = 0; k < length_; ++k) if (instruction[k].number == tmp.number) tmp_in_arr = k;
        if (tmp_in_arr == -1) {
            instruction.append(tmp);
            ++length_;
        } else {
            if (tmp.next[0] != -1) {
                tmp.next[1] = instruction[tmp_in_arr].next[1];
                tmp.action[1] = instruction[tmp_in_arr].action[1];
                instruction.pop();
                instruction.append(tmp);
            } else {
                tmp.next[0] = instruction[tmp_in_arr].next[0];
                tmp.action[0] = instruction[tmp_in_arr].action[0];
                instruction.pop();
                instruction.append(tmp);
            }
        }
    }
}

instructions::instructions(const instructions &X) {
    length_ = X.length_;
    instruction = X.instruction;
}

instructions &instructions::operator=(const instructions &X) {
    if (this != &X) {
        length_ = X.length_;
        instruction = X.instruction;
    }
    return *this;
}

instructions::Node instructions::get_first_q() {
    return instruction[0];
}

instructions::Node instructions::get_next_q(int i) {
    for (int k = 0; k < length_; ++k) {
        if (i == instruction[k].number) {
            return instruction[k];
        }
    }
    Node x;
    return x;
}

