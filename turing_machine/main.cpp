#include "turingmachine.h"
#include <fstream>

int main(int argc, char **argv) {
    if (argc < 4) {
        return -4;
    }
    auto MT = std::ifstream(argv[1]);
    if (!MT) return -1;
    auto input = std::ifstream(argv[2]);
    if (!input) {
        MT.close();
        return -2;
    }
    auto output = std::ofstream(argv[3]);
    if (!output) {
        input.close();
        MT.close();
        return -3;
    }
    try {
        auto inst = instructions(MT);
        std::string input_date;
        int i = 0, j = 0;
        getline(input, input_date);
        while (input_date[j] != ' ')++j;
        int len = take_num_from_str(input_date, i, j);
        ++j;
        i = j;
        while (input_date[j] != ' ') ++j;
        int maxsteps = take_num_from_str(input_date, i, j);
        std::string init = input_date.substr(j + 1, input_date.size() - 1);
        auto Machine = turing_machine(len, inst);
        auto answ = Machine.calc(init, maxsteps);
        if (answ == "Not applicable") {
            output << answ;
        } else {
            len = (int) answ.length() - 1;
            while (answ[len] != '1') --len;
            for (int k = 0; k <= len; ++k) {
                output << answ[k];
            }
        }
    }
    catch (std::invalid_argument &err) {
        output << "Error";
    }
    MT.close();
    input.close();
    output.close();
    return 0;
}
