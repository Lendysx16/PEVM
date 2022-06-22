#pragma once
#include "avl_tree.h"
#include "bitifstream.h"
#include "dynamic_array.h"

class lzw_method{
    static int length_of_tree;
    static int length_of_bits;
    struct codes_of_sym{
        std::string str;
        int code;
        explicit codes_of_sym(int code = 0, std::string str = ""){
            this->code = code;
            this->str = std::move(str);
        };
        explicit codes_of_sym(int code = 0, char str = 0){
            this->code = code;
            this->str = str;
        };
        friend bool operator<(const codes_of_sym &left, const codes_of_sym &right) {
                return left.str < right.str;
        }
        friend bool operator>(const codes_of_sym &left, const codes_of_sym &right){
                return left.str > right.str;
        }
        friend bool operator==(const codes_of_sym &left, const codes_of_sym &right){
            return left.str == right.str;
        }
    };
    static void put_code_to_file(obitfstream&, int code);
public:
    static void compress(std::ifstream&, obitfstream&);
    static void decompress(ibitfstream&, std::ofstream&);
};

int lzw_method::length_of_tree = 0;
int lzw_method::length_of_bits = 0;
void lzw_method::compress(std::ifstream &in, obitfstream &out){
    length_of_tree = -1;
    length_of_bits = 9;
    out << 'l';
    avltree<codes_of_sym> tree;
    for(auto i = 0; i < 256; ++i){
        tree.insert(codes_of_sym((++length_of_tree), (char)(length_of_tree)));
    }
    std::string currstring;
    while(in.peek() != EOF){
        auto ch = (char)in.get();
        auto new_string = currstring + (char)ch;
        auto it = tree.find(codes_of_sym(-1, new_string));
        if(it != nullptr){
            currstring = new_string;
        }
        else{
           auto it_to_put = (*tree.find(codes_of_sym(-1, currstring))).code;
           put_code_to_file(out, it_to_put);
           tree.insert(codes_of_sym(++length_of_tree, new_string));
           currstring = ch;
        }
    }
    if(!currstring.empty()){
        auto it_to_put = (*tree.find(codes_of_sym(-1, currstring))).code;
        put_code_to_file(out, it_to_put);
    }
    out.put_buffer();
}

void lzw_method::put_code_to_file(obitfstream &out, int code) {
    if(1 << length_of_bits <= length_of_tree) ++length_of_bits;
    auto seq = dynamic_array<bool>(length_of_bits);
    for(auto  i = 0; i <= length_of_bits; ++i){
        seq[i] = false;
    }
    for(int i = length_of_bits - 1; i > -1; --i){
        if(code){
            seq[i] = (code % 2);
            code /= 2;
        }
        else{
            break;
        }
    }
    for(int i = 0 ; i < length_of_bits; ++i){
        out.putBit(seq[i]);
    }
}


void lzw_method::decompress(ibitfstream &in, std::ofstream &out) {
    if(in.peek() != 'l') throw std::invalid_argument("Wrong input file");
    in.get();
    length_of_tree = -1;
    length_of_bits = 9;
    dynamic_array<std::string> accses_to_codes(256);
    for(auto i = 0; i < 256; ++i){
        ++length_of_tree;
        std::string sym;
        sym += (char)i;
        accses_to_codes.append(sym);
    }
    std::string last_string, string_to_put, string_to_add;
    while(in.peek() != EOF){
        if(1 << length_of_bits <= length_of_tree + 1) ++length_of_bits;
        int code = 0;
        for(auto i = length_of_bits - 1; i > -1; --i){
            code += ((int)in.getBit() << i);
        }
        //std::cout << " " << code  << "   "<< length_of_tree<< std::endl;
        if(code <= length_of_tree){
            string_to_put = accses_to_codes[code];
            out << string_to_put;
            // std::cout << string_to_put << " " << string_to_add << std::endl;
            string_to_add = last_string + string_to_put[0];
            if(string_to_add.size() > 1){
            accses_to_codes.append(string_to_add);
                ++length_of_tree;
            }
            last_string = string_to_put;
        }
        else{
            string_to_put = last_string + last_string[0];
            out << string_to_put;
            accses_to_codes.append(string_to_put);
            last_string = string_to_put;
            ++length_of_tree;
        }
    }
}