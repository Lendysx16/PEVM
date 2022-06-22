#pragma once
#ifndef HUFFMAN_METHOD_NODE
#define HUFFMAN_METHOD_NODE


namespace symbols {
    struct Node {
        explicit Node(const unsigned char sym = 0, int freq = 0) : sym_(sym), freq_(freq) {};
        unsigned char sym_;
        int freq_;
        bool eof_ = false;
    };
}

namespace tree {
    struct Node {
        Node *left = nullptr, *right = nullptr;
        symbols::Node value;
        bool eof_ = false;

        explicit Node(symbols::Node valuex = symbols::Node(), Node *leftx = nullptr, Node *rightx = nullptr,
                      bool eof = false) : value(valuex), left(leftx), right(rightx), eof_(eof) {
        }

        ~Node() {
            delete left;
            delete right;
            left = right = nullptr;
        }
    };
}

bool operator>(const symbols::Node &x1, const symbols::Node &x2) {
    if (x1.freq_ != x2.freq_)
        return x1.freq_ < x2.freq_;
    else { return x1.sym_ > x2.sym_; }
}


bool operator<(const symbols::Node &x1, const symbols::Node &x2) {
    return x2 > x1;
}

std::ostream &operator<<(std::ostream &out, symbols::Node &x) {
    out << x.sym_ << " - " << x.freq_;
    return out;
}


bool operator>(const tree::Node &x1, const tree::Node &x2) {
    return x1.value > x2.value;
}

bool operator<(const tree::Node &x1, const tree::Node &x2) {
    return x2 > x1;
}


std::ostream &operator<<(std::ostream &out, tree::Node *x) {
    out << x->value;
    return out;
}


size_t partition(tree::Node **nums, size_t l, size_t r) {
    auto pivot = nums[(l + r) / 2]->value;
    size_t i = l, j = r;
    while (i <= j) {
        while (nums[i]->value < pivot) {
            i += 1;
        }
        while (nums[j]->value > pivot) {
            j -= 1;
        }

        if (i >= j) {
            break;
        }
        std::swap(nums[i], nums[j]);
        i += 1;
        j -= 1;
    }
    return j;
}

void quicksort(tree::Node **nums, size_t l, size_t r) {
    if (l < r) {
        size_t q = partition(nums, l, r);
        quicksort(nums, l, q);
        quicksort(nums, q + 1, r);
    }
}


#endif
