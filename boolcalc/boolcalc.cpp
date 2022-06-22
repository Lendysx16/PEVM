#include <iostream>
#include "boolexpr.h"
#include <fstream>

void help();

int main(int argc, char *argv[]) {
    if (argc < 4) {
        std::cout << "Not enough arguments" << std::endl;
        help();
        return 1;
    }
    std::string helpstr = argv[1];
    if (helpstr == "-h" or helpstr == "-?") {
        help();
        return 0;
    }
    std::ifstream in(argv[2]);
    if (!in) {
        std::cout << "Can't open input file" << std::endl;
        in.close();
        return 1;
    }
    std::ofstream out(argv[3]);
    if (!out) {
        std::cout << "Can't open output file" << std::endl;
        in.close();
        out.close();
        return 1;
    }
    try {
        std::vector<BooleanExpression> vec;
        char func_str[256];
        int size = 0;
        char ch;

        while (in.peek() != EOF) {
            ch = (char) in.get();
            if (ch == '\n') {
                if (func_str[0] != '\0') {
                    vec.emplace_back(func_str);
                    func_str[0] = '\0';
                    size = 0;
                }
            } else {
                func_str[size++] = ch;
                func_str[size] = '\0';
            }
        }
        if (func_str[0] != '\0') {
            vec.emplace_back(func_str);
        }
        if (helpstr == "-calc") {
            for (auto &func: vec) {
                std::cout << "Enter arguments for " << std::string(func) << ": " << std::endl;
                out << func.calc() << std::endl;
            }
            return 0;
        }
        if (helpstr == "-cnf") {
            for (auto &func: vec) {
                out << std::string(func.cnf()) << std::endl;
            }
            return 0;
        }
        if (helpstr == "-dnf") {
            for (auto &func: vec) {
                out << std::string(func.dnf()) << std::endl;
            }
            return 0;
        }
        if (helpstr == "-zh") {
            for (auto &func: vec) {
                out << std::string(func.zhegalkin()) << std::endl;
            }
            return 0;
        }
        if (helpstr == "-table") {
            for (auto &func: vec) {
                func.truthtable();
            }
        }
        if (helpstr == "-isfull") {
            Fullsystem fs(vec);
            out << (Fullsystem::isFullSystem(fs) ? "yes" : "no");
            return 0;
        }
    }

catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    in.close();
    out.close();
    return 1;
}

return 0;
}


void help() {
    std::cout << "Usage: <func> <input_file> <output_file>" << std::endl;
    std::cout << "list of functions: " << std::endl;
    std::cout << "-calc, -cnf, -dnf, -zh, -table, -isfull" << std::endl;
}
