#include "bitifstream.h"

#ifndef HUFFMAN_METHOD_TREE
#define HUFFMAN_METHOD_TREE

struct table{
    unsigned char b_;
    std::string code_;
    bool eof_ = false;
    explicit table(const unsigned char b = 0, std::string code = "", bool eof = false){
        b_ = b;
        code_ = std::move(code);
        eof_ = eof;
    };
};

std::ostream &operator<<(std::ostream &out, table &x) {
    out << x.b_ << "   -    " << x.code_;
    return out;
}
obitfstream &operator<<(obitfstream &out, table &x) {
    out << x.b_;
    out << (unsigned char)x.code_.size();
    auto k = (x.code_.size() < 8 ? 8 - x.code_.size():  ((x.code_.size() / 8) + 1) * 8 - x.code_.size()) + x.code_.size();
    for(auto i = 0; i < k; ++i){
        if(i < x.code_.size())
        out.putBit(static_cast<bool>(x.code_[i] - '0'));
        else{
            out.putBit(false);
        }
    }
    return out;
}
bool operator>(const table &x1, const table &x2){
    return x1.code_.size() < x2.code_.size();
}
bool operator<(const table &x1, const table &x2){
    return x1.code_.size() > x2.code_.size();
}
#endif


