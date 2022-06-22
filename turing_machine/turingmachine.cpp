#include "turingmachine.h"


int take_num_from_str(const std::string &str, int pstart, int pend) {
    int tengrade = 1, number = 0;
    for (auto k = pend - 1; k >= pstart; --k) {
        if (str[k] < '0' or str[k] > '9') throw std::invalid_argument(str);
        number += tengrade * (str[k] - '0');
        tengrade *= 10;
    }
    return number;
}


std::string turing_machine::calc(const std::string &init, int maxsteps) {
    std::string answ;
    auto condition = inst.get_first_q();
    int action;
    int current_steps = 0, current_position_on_lent = 0;
    for (int i = 0; i < init.size(); ++i) {
        lent[i] = (take_num_from_str(init, i, i + 1));
    }
    while (current_steps < maxsteps) {
        ++current_steps;
        if (lent[current_position_on_lent] == 0) {
            action = condition.action[0];
            condition = inst.get_next_q(condition.next[0]);
        } else {
            action = condition.action[1];
            condition = inst.get_next_q(condition.next[1]);
        }
        switch (action) {
            case 1: {
                lent[current_position_on_lent] = 0;
                --current_position_on_lent;
                break;
            }
            case 2: {
                lent[current_position_on_lent] = 0;
                break;
            }
            case 3: {
                lent[current_position_on_lent] = 0;
                ++current_position_on_lent;
                break;
            }
            case 4: {
                lent[current_position_on_lent] = 1;
                --current_position_on_lent;
                break;
            }
            case 5: {
                lent[current_position_on_lent] = 1;
                break;
            }
            case 6: {
                lent[current_position_on_lent] = 1;
                ++current_position_on_lent;
                break;
            }
            default: {
                for (int k = 0; k < lent.get_len(); ++k) {
                    answ += static_cast<char>(lent[current_position_on_lent + k] + '0');
                }
                return answ;
            }
        }
    }
    return "Not applicable";
}