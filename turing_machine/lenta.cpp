#include "lenta.h"


Lenta::Lenta(int length){
    sequence_ = dynamic_array<int>(length);
    length_ = length;
    for(int i = 0; i < length; ++i) sequence_.append(0);
}
int &Lenta::operator[](int i){
    i %= length_;
    if(i < 0) i = length_ + i;
    return sequence_[i];
}

Lenta::Lenta(const Lenta& X){
    length_ = X.length_;
    sequence_ = X.sequence_;
}
Lenta &Lenta::operator=(const Lenta&X){
    if(this != &X){
        length_ = X.length_;
        sequence_ = X.sequence_;
    }
    return *this;
}


