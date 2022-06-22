#pragma once
#include <iostream>
#include "node_struct.h"
#include "dynamic_array.h"
#include "bitifstream.h"
#include "table_struct.h"




class huffman_method{
private:
    static void build_table(tree::Node *, std::string &, dynamic_array<table> &);
public:
    static void compress(std::ifstream &, obitfstream &);
    static void decompress (ibitfstream &, std::ofstream &);
};



void huffman_method::build_table(tree::Node *root, std::string &x, dynamic_array<table> &answ) {
    if ((!root->left) and (!root->right)) {
        auto tmp = table((root->value.sym_), x);
        if (root->eof_)
            answ[256] = (tmp);
        else
            answ[root->value.sym_] = (tmp);
    }
    if (root->left) {
        x += '0';
        build_table(root->left, x, answ);
        x.pop_back();
    }
    if (root->right) {
        x += '1';
        build_table(root->right, x, answ);
        x.pop_back();
    }
}

void huffman_method::compress(std::ifstream &file, obitfstream &out) {
    auto b = dynamic_array<symbols::Node>(257);
    for (int i = 0; i < 256; ++i) {
        b.append(symbols::Node((i)));
    }
    while (file.peek() != EOF) {
        b[file.get()].freq_ += 1;
    }
    b.sort();
    int cnt = 0;
    while (b[cnt].freq_ != 0) {
        ++cnt;
    }
    b.pop(256 - cnt);
    auto huftree = dynamic_array<tree::Node *>(b.get_elements_used());
    for (auto i = 0; i < b.get_elements_used(); ++i) {
        auto tmp = new tree::Node;
        tmp->value = b[i];
        huftree.append(tmp);
        tmp = nullptr;
        delete tmp;
    }
    huftree.append(new tree::Node(symbols::Node('e', 1), nullptr, nullptr, true));
    cnt = 0;
    auto x = std::string("");
    auto finale_table = dynamic_array<table>(257);
    for (unsigned short i = 0; i < 257; ++i) {
        finale_table.append(table());
    }
    while (huftree.get_elements_used() != 1) {
        //print(huftree);
        ++cnt;
        auto tmp1 = huftree[static_cast<int>(huftree.get_elements_used() - 1)];
        huftree.pop();
        auto tmp2 = huftree[static_cast<int>(huftree.get_elements_used() - 1)];
        huftree.pop();
        symbols::Node tmp3(0, tmp1->value.freq_ + tmp2->value.freq_);
        auto tmp4 = new tree::Node;
        tmp4->right = tmp1;
        tmp4->left = tmp2;
        tmp4->value = tmp3;
        huftree.append(tmp4);
        huftree.sort();

    }
    auto root = *huftree[0];
    build_table(&root, x, finale_table);
    file.clear();
    file.seekg(0, std::ios::beg);
    out << 'h';
    out << finale_table[256];
    for (auto i = 0; i < 256; ++i)
        if (!finale_table[i].code_.empty())
            out << finale_table[i];
    for (auto i = 0; i < 256; ++i) {
        if (!finale_table[i].code_.empty()) {
            out << finale_table[i];
            break;
        }
    }
    while (file.peek() != EOF) {
        std::string tmp = finale_table[file.get()].code_;
        for (auto i: tmp) {
            out.putBit(static_cast<bool>(i - '0'));
        }
    }
    for(auto i : finale_table[256].code_){
        out.putBit(i - '0');
    }
    out.put_buffer();
}



void huffman_method::decompress(ibitfstream &x, std::ofstream &y) {
    if(x.peek() != 'h') throw std::invalid_argument("Wrong input file");
    x.get();
    auto root = new tree::Node(symbols::Node(0, 0));
    tree::Node *current_node;
    bool break_flag = false;
    int steps = -1;
    while (true) {
        ++steps;
        current_node = root;
        if (break_flag) break;
        auto sym = (unsigned char) x.get();
        auto len = (unsigned int) x.get();
        auto bits_len = (len < 8 ? 8 - len : ((len / 8) + 1) * 8 - len) + len;
        auto str = std::string();
        for (auto i = 0; i < bits_len; ++i) {
            if (i < len)
                str += std::to_string((int) x.getBit());
            else { x.getBit(); }
        }
        for (auto i = 0; i < str.size(); ++i) {
            if (str[i] == '0') {
                if (current_node->left and i == str.size() - 1 and current_node->left->value.sym_ == sym) {
                    break_flag = true;
                    break;
                }
                if (!current_node->left)
                    current_node->left = new tree::Node;
                current_node = current_node->left;
                if (i == str.size() - 1) {
                    current_node->value.sym_ = sym;
                    if(steps == 0) {current_node->value.eof_ = true;
                    }
                    break;
                }
            } else if (str[i] == '1') {
                if (current_node->right and i == str.size() - 1 and current_node->right->value.sym_ == sym) {
                    break_flag = true;
                    break;
                }
                if (!current_node->right)
                    current_node->right = new tree::Node;
                current_node = current_node->right;
                if (i == str.size() - 1) {
                    current_node->value.sym_ = sym;
                    if(steps == 0) {current_node->value.eof_ = true;
                    }
                    break;
                }
            }
        }
    }

    unsigned char bit;
    current_node = root;
    break_flag = false;
    while (!break_flag) {
        bit = x.getBit() + '0';
              if (bit == '0') {
            if (current_node->left) {
                current_node = current_node->left;
            }
            if (!current_node->left and !current_node->right) {
                if(current_node->value.eof_){
                    break_flag = true;
                    break;
                }
                y.put((char) current_node->value.sym_);
                current_node = root;
            }

        } else if (bit == '1') {
            if (current_node->right) {
                current_node = current_node->right;
            }
            if (current_node->left == nullptr and current_node->right == nullptr) {
                if(current_node->value.eof_){
                    break_flag = true;
                    break;
                }
                y.put((char) current_node->value.sym_);
                current_node = root;
            }
        }
    }
    delete root;
    root = nullptr;
}


