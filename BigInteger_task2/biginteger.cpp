#include "biginteger.h"


std::string to_string(const BigInteger &X) {
    if (X == 0) return (std::string) "0";
    std::string answ;
    if (X.size_ == 1) {
        if (X.sign_) answ += "-";
        answ += std::to_string(X.num_[0]);
        return answ;
    } else {
        auto tmp = X;
        while (tmp != 0) {
            int carry = 0;
            for (auto i = 0; i < tmp.get_size(); ++i) {
                unsigned long long cur = tmp[i] + carry * two_in_32;
                tmp.num_[i] = (cur / 10);
                carry = (int) (cur % 10);
            }
            answ += std::to_string(carry);
            if (tmp[0] == 0) {
                tmp.delete_zeros();
            }
        }
    }
    if (X.sign_) answ += "-";
    auto answ1 = answ;
    for(auto i = 0; i < answ.size(); ++i){
        answ[i] = answ1[answ.size() - 1 - i];
    }
    return answ;
}

std::ostream &operator<<(std::ostream &out, const BigInteger &X) {
    out << to_string(X);
    return out;
}

bool check_for_zeros(const unsigned long long *arr, size_t len) {
    for (auto i = 0; i < len; ++i) {
        if (arr[i] != 0) return true;
    }
    return false;
}


BigInteger::BigInteger(const std::string &X) {
    std::string str;
    sign_ = X[0] == '-';
    if(sign_ and X.size() == 1 or X.empty()) throw std::invalid_argument(X);
    auto start = X.rbegin();
    auto end = sign_ ? X.rend() - 1 : X.rend();
    auto len = X.size() >= 10 ? X.size() / 9 + 1 : 1;
    auto tmp = new unsigned long long[len];
    for (auto i = 0; i < len; ++i) tmp[i] = 0;
    unsigned int i = 0;
    unsigned long long tengrade = 1;
    while (start != end) {
        if((*start) > '9' || *start < '0') throw std::invalid_argument(X);
        tmp[len - i / 9 - 1] += (*start - '0') * tengrade;
        ++i;
        ++start;
        if (i % 9 == 0) tengrade = 1;
        else tengrade *= 10;
    }
    delete num_;
    num_ = new unsigned int[len];
    for (auto k = 0; k < len; ++k) num_[k] = 0;
    unsigned long long carry, diff;
    size_t index = 0;
    while (check_for_zeros(tmp, len)) {
        carry = 0;
        for (auto k = 0; k < len; ++k) {
            diff = tmp[k] + carry * 1000000000;
            tmp[k] = (diff / two_in_32);
            carry = (diff % two_in_32);
        }
        num_[len - ++index] = carry;
    }
    size_ = len;
    delete_zeros();
}

BigInteger::BigInteger(unsigned long long X) {
    auto num = X;
    if (num < two_in_32) {
        num_ = new unsigned int[1];
        num_[0] = num;
        size_ = 1;
    } else {
        size_ = 2;
        num_ = new unsigned int[2];
        num_[0] = num / two_in_32;
        num_[1] = num % two_in_32;
    }
}

BigInteger::BigInteger(const BigInteger &X) {
    sign_ = X.sign_;
    size_ = X.size_;
    num_ = new unsigned int[size_];
    for (auto i = 0; i < size_; ++i) {
        num_[i] = X.num_[i];
    }
}

BigInteger::BigInteger(BigInteger &&X) noexcept {
    sign_ = X.sign_;
    size_ = X.size_;
    num_ = X.num_;
    X.num_ = nullptr;
    X.size_ = 0;
}

BigInteger::BigInteger(long long X) {
    auto num = X;
    if (num < 0) {
        sign_ = true;
        num *= -1;
    }
    if (num < two_in_32) {
        num_ = new unsigned int[1];
        num_[0] = num;
        size_ = 1;
    } else {
        size_ = 2;
        num_ = new unsigned int[2];
        num_[0] = num / two_in_32;
        num_[1] = num % two_in_32;
    }
}

bool operator>(const BigInteger &x1, const BigInteger &x2) {
    auto sign1 = x1.get_sign(), sign2 = x2.get_sign();
    auto size1 = x1.get_size(), size2 = x2.get_size();
    if (sign1 == sign2) {
        if (sign1) {
            if (size1 > size2) return false;
            if (size2 > size1) return true;
            for (auto i = 0; i < size1; ++i) {
                if (x1[i] == x2[i]) continue;
                if (x1[i] < x2[i]) return true;
                if (x1[i] > x2[i]) return false;
            }
            return true;
        } else {
            if (size1 > size2) return true;
            if (size2 > size1) return false;
            for (auto i = 0; i < size1; ++i) {
                if (x1[i] == x2[i]) continue;
                if (x1[i] < x2[i]) return false;
                if (x1[i] > x2[i]) return true;
            }
            return false;
        }
    }
    if (sign1) {
        return false;
    }
    return true;
}

bool operator==(const BigInteger &x1, const BigInteger &x2) {
    auto sign1 = x1.get_sign(), sign2 = x2.get_sign();
    auto size1 = x1.get_size(), size2 = x2.get_size();
    if (x1[0] == 0 and size1 == 1 and x2[0] == 0 and size2 == 1) return true;
    if (sign1 == sign2) {
        if (size1 == size2) {
            for (auto i = 0; i < size1; ++i) {
                if (x1[i] != x2[i]) return false;
            }
            return true;
        }
    }
    return false;
}

bool operator!=(const BigInteger &x1, const BigInteger &x2) {
    return !(x1 == x2);
}

bool operator<(const BigInteger &x1, const BigInteger &x2) {
    return x2 > x1;
}

bool operator>=(const BigInteger &x1, const BigInteger &x2) {
    return !(x1 < x2);
}

bool operator<=(const BigInteger &x1, const BigInteger &x2) {
    return !(x1 > x2);
}

bool BigInteger::abs_cmp(const BigInteger &X) {
    if (X.sign_ == sign_) {
        if (sign_) {
            return *this < X;
        }
        return *this > X;
    }
    bool result;
    if (sign_) {
        sign_ = false;
        result = *this > X;
        sign_ = true;
        return result;
    } else {
        sign_ = true;
        result = *this < X;
        sign_ = false;
        return result;
    }
}

BigInteger &BigInteger::operator=(const BigInteger &X) {
    if (this != &X) {
        delete[] num_;
        sign_ = X.sign_;
        size_ = X.size_;
        num_ = new unsigned int[size_];
        for (auto i = 0; i < size_; ++i) num_[i] = X[i];
    }
    return *this;
}
BigInteger &BigInteger::operator=(const std::string &X){
    *this = std::move(BigInteger(X));
    return *this;
}
BigInteger &BigInteger::operator=(BigInteger &&X) noexcept {
    if (this != &X) {
        delete[] num_;
        sign_ = X.sign_;
        size_ = X.size_;
        num_ = X.num_;
        X.num_ = nullptr;
        X.size_ = 0;
    }
    return *this;
}

BigInteger BigInteger::mult_two_long(const BigInteger &X) {
    auto new_size = this->size_ + X.size_;
    BigInteger tmp = 0;
    tmp.resize(new_size);
    for (int i = 0; i < new_size; ++i) {
        tmp.num_[i] = 0;
    }
    unsigned int carry = 0;
    unsigned long long cur;
    for (auto i = 0; i < this->size_; ++i) {
        for (auto j = 0; j < X.size_ || carry; ++j) {
            cur = (unsigned long long) tmp.num_[new_size - i - j - 1] +
                  (unsigned long long) this->num_[this->size_ - i - 1] *
                  (unsigned long long) (j < X.size_ ? X[X.size_ - j - 1] : 0) + carry;
            tmp.num_[new_size - i - j - 1] = cur % two_in_32;
            carry = cur / two_in_32;
        }
    }
    if (tmp[0] == 0) {
        tmp.delete_zeros();
    }
    return std::move(tmp);
}

BigInteger &BigInteger::operator*=(const BigInteger &X) {
    bool sign = sign_ ^ X.sign_;
    *this = this->mult_two_long(X);
    this->sign_ = sign;
    return *this;
}

BigInteger BigInteger::bin_mod(const BigInteger &X) {
    BigInteger left = 0;
    BigInteger mult = 0;
    BigInteger carry = 0;
    BigInteger mid = 0;
    auto absX = X;
    absX.sign_ = false;
    auto xcopy = *this;
    xcopy.sign_ = false;
    while (left <= xcopy) {
        mid = (left + xcopy) >> 1;
        carry = *this - mid * absX;
        mult = mid * absX;
        carry.sign_ = false;
        if (mid >= (*this)) {
            return 0;
        }
        if (mult > (*this) and carry >= absX)
            xcopy = mid - 1;
        else if (mult < (*this) and carry >= absX)
            left = mid + 1;
        else {
            if (mult > *this)
                return std::move(carry - X);
            return std::move(carry);
        }
    }
    return 0;
}

BigInteger BigInteger::bin_division(const BigInteger &X) {
    BigInteger left = 0;
    BigInteger mult = 0;
    BigInteger carry = 0;
    BigInteger mid = 0;
    auto absX = X;
    absX.sign_ = false;
    auto xcopy = *this;
    xcopy.sign_ = false;
    while (left <= xcopy) {
        mid = (left + xcopy).division_on_small_num(2);
        carry = *this - mid * absX;
        mult = mid * absX;
        carry.sign_ = false;
        if (mid >= (*this)) {
            return 0;
        }
        if (mult > (*this) and carry >= absX)
            xcopy = mid - 1;
        else if (mult < (*this) and carry >= absX)
            left = mid + 1;
        else {
            if (mult > *this)
                return std::move(mid - 1);
            return std::move(mid);
        }
    }
    return 0;
}

BigInteger BigInteger::division_on_small_num(const BigInteger &X) {
    auto small_num = X[0];
    BigInteger tmp = *this;
    unsigned int carry = 0;
    for (auto i = 0; i < tmp.size_; ++i) {
        unsigned long long cur = tmp[i] + carry * two_in_32;
        tmp.num_[i] = (cur / small_num);
        carry = (int) (cur % small_num);
    }
    if (tmp[0] == 0) {
        tmp.delete_zeros();
    }

    return std::move(tmp);
}

BigInteger BigInteger::mod_on_small_num(const BigInteger &X) {
    if (X == 0) throw std::invalid_argument(nullptr);
    auto small_num = X[0];
    BigInteger tmp = *this;
    unsigned int carry = 0;
    for (auto i = 0; i < tmp.size_; ++i) {
        unsigned long long cur = tmp[i] + carry * two_in_32;
        tmp.num_[i] = (cur / small_num);
        carry = (int) (cur % small_num);
    }
    if (tmp[0] == 0) {
        tmp.delete_zeros();
    }

    return std::move(BigInteger(carry));
}

BigInteger &BigInteger::operator/=(const BigInteger &X) {
    if (X == 0) throw std::invalid_argument("Zero division.");
    auto sign = X.sign_ ^ sign_;
    sign_ = false;
    if (X.size_ == 1) {
        *this = division_on_small_num(X);
    } else {
        *this = bin_division(X);
    }
    this->sign_ = sign;
    return *this;
}

BigInteger &BigInteger::operator%=(const BigInteger &X) {
    if (X == 0) throw std::invalid_argument(nullptr);
    auto sign = sign_;
    if (X.size_ == 1) {
        *this = mod_on_small_num(X);
    } else {
        *this = bin_mod(X);
    }
    this->sign_ = sign;
    return *this;
}

BigInteger BigInteger::add_num_with_same_sign(const BigInteger &X) {
    BigInteger tmp = 0;
    auto new_size = std::max(size_, X.size_) + 1;
    tmp.resize(new_size);
    for (int i = 0; i < new_size; ++i) {
        tmp.num_[i] = 0;
    }
    int carry = 0;
    unsigned long long sum;
    for (auto i = 0; i < new_size || carry; ++i) {
        sum = (i < size_ ? (*this)[this->size_ - i - 1] : 0) + (unsigned long long) carry +
              (i < X.size_ ? X[X.size_ - i - 1] : 0);
        carry = (sum >= two_in_32) ? 1 : 0;
        if (carry > 0) tmp.num_[new_size - i - 1] = sum - two_in_32;
        else tmp.num_[new_size - i - 1] = sum;
    }
    tmp.delete_zeros();
    return std::move(tmp);

}

BigInteger &BigInteger::operator+=(const BigInteger &X) {
    if (sign_ == X.sign_) {
        *this = add_num_with_same_sign(X);
        this->sign_ = X.sign_;
    } else {
        if (sign_) {
            if (abs_cmp(X)) {
                *this = substract_with_same_sign(X);
                this->sign_ = true;
            } else {
                auto tmp = X;
                *this = tmp.substract_with_same_sign(*this);
                this->sign_ = false;
            }
        } else {
            if (abs_cmp(X)) {
                *this = substract_with_same_sign(X);
                this->sign_ = false;
            } else {
                auto tmp = X;
                *this = tmp.substract_with_same_sign(*this);
                this->sign_ = true;
            }
        }
    }
    return *this;
}

BigInteger BigInteger::substract_with_same_sign(const BigInteger &X) {
    BigInteger tmp = 0;
    tmp.resize(size_);
    for (int i = 0; i < size_; ++i) {
        tmp.num_[i] = 0;
    }
    bool carry = false;
    int64_t diff;
    for (auto i = 1; i < size_ + 1 || carry; ++i) {
        diff = (int64_t) num_[size_ - i] - carry - (int64_t) (i < X.size_ + 1 ? X[X.size_ - i] : 0);
        carry = diff < 0;
        if (carry) diff += two_in_32;
        tmp.num_[size_ - i] = (unsigned long) (diff);
    }
    tmp.delete_zeros();
    return std::move(tmp);
}

BigInteger &BigInteger::operator-=(const BigInteger &X) {
    if (sign_ == X.sign_) {
        if (abs_cmp(X)) {
            *this = substract_with_same_sign(X);
            this->sign_ = X.sign_;
        } else {
            auto tmp = X;
            *this = tmp.substract_with_same_sign(*this);
            this->sign_ = !X.sign_;
        }
    } else if (sign_) {
        *this = add_num_with_same_sign(X);
        this->sign_ = true;
    } else {
        *this = add_num_with_same_sign(X);
        sign_ = false;
    }
    return *this;
}

BigInteger operator+(BigInteger X1, const BigInteger &X2) {
    X1 += X2;
    return std::move(X1);
}

BigInteger operator-(BigInteger X1, const BigInteger &X2) {
    X1 -= X2;
    return std::move(X1);
}

BigInteger operator*(BigInteger X1, const BigInteger &X2) {
    X1 *= X2;
    return std::move(X1);
}

BigInteger operator/(BigInteger X1, const BigInteger &X2) {
    X1 /= X2;
    return std::move(X1);
}

BigInteger operator%(BigInteger X1, const BigInteger &X2) {
    X1 %= X2;
    return std::move(X1);
}

BigInteger BigInteger::operator-() const {
    auto tmp = *this;
    if (tmp[0] != 0 or size_ > 1) {
        tmp.sign_ = !sign_;
    } else tmp.sign_ = false;
    return std::move(tmp);
}

BigInteger &BigInteger::operator+() {
    return *this;
}

BigInteger &BigInteger::operator--() {
    *this -= 1;
    return *this;
}

BigInteger BigInteger::operator--(int) {
    auto x = *this;
    *this -= 1;
    return std::move(x);
}

BigInteger &BigInteger::operator++() {
    *this += 1;
    return *this;
}

BigInteger BigInteger::operator++(int) {
    auto x = *this;
    *this += 1;
    return std::move(x);
}


BigInteger &BigInteger::operator|=(const BigInteger &X) {
    auto max_size = std::max(size_, X.size_);
    this->resize(max_size);
    bool sign = sign_ | X.sign_;
    if (sign_) {
        for (auto i = 0; i < size_; ++i)
            num_[i] = ~num_[i];
        *this -= 1;
    }
    auto tmp = X;
    if (X.sign_) {
        for (auto i = 0; i < tmp.size_; ++i)
            tmp.num_[i] = ~tmp.num_[i];
        tmp -= 1;
    }
    for (auto i = 0; i < max_size; ++i) {
        num_[size_ - i - 1] =
                num_[size_ - i - 1] | (i < tmp.size_ ? tmp.num_[tmp.size_ - i - 1] : -1ul * (int) (tmp.sign_));
    }
    this->sign_ = sign;
    if (sign) {
        for (auto i = 0; i < max_size; ++i)
            num_[i] = ~num_[i];
        *this -= 1;
    }

    delete_zeros();
    return *this;
}

BigInteger operator|(BigInteger X1, const BigInteger &X2) {
    X1 |= X2;
    return std::move(X1);
}


BigInteger &BigInteger::operator^=(const BigInteger &X) {
    auto max_size = std::max(size_, X.size_);
    this->resize(max_size);
    bool sign = sign_ ^ X.sign_;
    if (sign_) {
        for (auto i = 0; i < size_; ++i)
            num_[i] = ~num_[i];
        *this -= 1;
    }
    auto tmp = X;
    if (X.sign_) {
        for (auto i = 0; i < tmp.size_; ++i)
            tmp.num_[i] = ~tmp.num_[i];
        tmp -= 1;
    }
    for (auto i = 0; i < max_size; ++i) {
        num_[size_ - i - 1] =
                num_[size_ - i - 1] ^ (i < tmp.size_ ? tmp.num_[tmp.size_ - i - 1] : -1ul * (int) (tmp.sign_));
    }
    this->sign_ = sign;
    if (sign) {
        for (auto i = 0; i < max_size; ++i)
            num_[i] = ~num_[i];
        *this -= 1;
    }

    delete_zeros();
    return *this;
}

BigInteger operator&(BigInteger X1, const BigInteger &X2) {
    X1 &= X2;
    return std::move(X1);
}

BigInteger &BigInteger::operator&=(const BigInteger &X) {
    auto max_size = std::max(size_, X.size_);
    this->resize(max_size);
    bool sign = sign_ & X.sign_;
    if (sign_) {
        for (auto i = 0; i < size_; ++i)
            num_[i] = ~num_[i];
        *this -= 1;
    }
    auto tmp = X;
    if (X.sign_) {
        for (auto i = 0; i < tmp.size_; ++i)
            tmp.num_[i] = ~tmp.num_[i];
        tmp -= 1;
    }
    for (auto i = 0; i < max_size; ++i) {
        num_[size_ - i - 1] =
                num_[size_ - i - 1] & (i < tmp.size_ ? tmp.num_[tmp.size_ - i - 1] : -1ul * (int) (tmp.sign_));
    }
    this->sign_ = sign;
    if (sign) {
        for (auto i = 0; i < max_size; ++i)
            num_[i] = ~num_[i];
        *this -= 1;
    }

    delete_zeros();
    return *this;
}

BigInteger operator^(BigInteger X1, const BigInteger &X2) {
    X1 ^= X2;
    return std::move(X1);
}

BigInteger BigInteger::operator~() {
    auto tmp = *this;
    tmp += 1;
    tmp.sign_ = !sign_;
    return std::move(tmp);
}

BigInteger &BigInteger::operator<<=(int rhs) {
    unsigned int mask = two_in_32 - 1;
    if(rhs < 0) rhs = -rhs;
    size_t block = rhs / 32;
    size_t rest = rhs % 32;
    auto rest1 = rest > 0 ? 1 : 0;
    if(block) size_ += block;
    if(rest) ++size_;
    auto tmp = new unsigned int[size_];
    for(auto i = rest1; i < size_; ++i)
        tmp[i] = num_[i - rest1];
    for(auto i = size_ - block; i < size_; ++i)
        tmp[i] = 0;
    if(rest) tmp[0] = 0;
    unsigned int remain_next = 0;
    unsigned int remain_this;
    if(rest != 0) {
        for (auto i = 0; i < size_; ++i) {
            remain_this = remain_next;
            remain_next = tmp[size_ - i - 1] | (mask >> rest);
            tmp[size_ - i - 1] <<= rest;
            tmp[size_ - i - 1] |= (remain_this >> (32 - rest));
        }
    }
    num_ = tmp;
    tmp = nullptr;
    delete[] tmp;
    delete_zeros();
    return *this;
}

BigInteger &BigInteger::operator>>=(int rhs) {
    if(rhs < 0)rhs = -rhs;
    size_t block = rhs / 32;
    if(block > size_) {
        *this = BigInteger(0);
        return *this;}
    size_t rest = rhs % 32;
    unsigned int ost = 1 << (rest);
    unsigned int remain_next = 0;
    unsigned int remain_this;
    for(auto i = 0 ; i < size_ - block; ++i){
        remain_this = remain_next;
        remain_next = (num_[i] % ost);
        num_[i] >>= rest;
        num_[i] |= (remain_this << (32 - rest));
    }
    size_ -= block;
    auto tmp = new unsigned int[size_];
    if(block){
        for(auto i = 0; i < size_; ++i)
            tmp[i] = num_[i];
        num_ = tmp;
        tmp = nullptr;
        delete[] tmp;
    }
    delete_zeros();
    if(sign_) {sign_ = false;
        *this = ~(*this);}
    return *this;
}

BigInteger operator>>(BigInteger X1, int X2) {
    X1 >>= X2;
    return std::move(X1);
}
BigInteger operator<<(BigInteger X1, int X2) {
    X1 <<= X2;
    return std::move(X1);
}
