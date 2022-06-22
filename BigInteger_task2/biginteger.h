#pragma once

#include <string>
#include <iostream>


constexpr long long two_in_32 = 1ll << 32;


class BigInteger {
private:
    unsigned int *num_ = nullptr;
    size_t size_ = 0;
    bool sign_ = false;

    void resize(size_t i) {
        if (i > size_) {
            auto diff = i - size_;
            auto *tmp = new unsigned int[i];
            for (auto k = 0; k < size_; ++k) {
                tmp[k + diff] = num_[k];
            }
            for (auto k = 0; k < diff; ++k) {
                tmp[k] = 0;
            }
            size_ = i;
            delete[] num_;
            num_ = tmp;
            tmp = nullptr;
            delete[] tmp;
        }
    };

    void delete_zeros() {
        int needless_zeros = 0;
        while (num_[needless_zeros] == 0 and needless_zeros < size_ - 1) ++needless_zeros;
        if (needless_zeros > 0 and needless_zeros != size_) {
            size_ -= needless_zeros;
            auto tmp = new unsigned[size_];
            for (auto i = 0; i < size_; ++i) {
                tmp[i] = num_[i + needless_zeros];
            }
            delete[] num_;
            num_ = tmp;
            tmp = nullptr;
            delete[] tmp;
        } else if (needless_zeros == size_) {
            delete[] num_;
            size_ = 1;
            num_ = new unsigned int[1];
            num_[0] = 0;
        }
    }

public:

    BigInteger(){
        delete[] num_;
        num_ = new unsigned int[1];
        num_[0] = 0;
        size_ = 1;
        sign_ = false;
    };

    BigInteger(const std::string &);

    BigInteger(long long);

    BigInteger(unsigned long long);

    BigInteger(unsigned int X) : BigInteger((unsigned long long) X) {};

    BigInteger(unsigned long X) : BigInteger((unsigned long long) X) {};

    BigInteger(unsigned short X) : BigInteger((unsigned long long) X) {};

    BigInteger(long X) : BigInteger((long long) X) {};

    BigInteger(int X) : BigInteger((long long) X) {};

    BigInteger(short X) : BigInteger((long long) X) {};

    BigInteger(const BigInteger &X);

    BigInteger(BigInteger &&X) noexcept;

    ~BigInteger() {
        delete[] num_; }

    unsigned int operator[](size_t i) const { return num_[i]; };

    BigInteger &operator+=(const BigInteger &);
    BigInteger &operator-=(const BigInteger &);
    BigInteger &operator*=(const BigInteger &);
    BigInteger &operator/=(const BigInteger &);
    BigInteger &operator%=(const BigInteger &);
    BigInteger &operator|=(const BigInteger &);
    BigInteger &operator^=(const BigInteger &);
    BigInteger &operator&=(const BigInteger &);
    BigInteger operator~();
    BigInteger &operator >>=(int rhs);
    BigInteger &operator <<=(int rhs);


    friend BigInteger operator+(BigInteger, const BigInteger &);
    friend BigInteger operator-(BigInteger, const BigInteger &);
    friend BigInteger operator*(BigInteger, const BigInteger &);
    friend BigInteger operator/(BigInteger, const BigInteger &);
    friend BigInteger operator%(BigInteger, const BigInteger &);
    friend BigInteger operator|(BigInteger, const BigInteger &);
    friend BigInteger operator^(BigInteger, const BigInteger &);
    friend BigInteger operator&(BigInteger, const BigInteger &);
    friend BigInteger operator<<(BigInteger, int);
    friend BigInteger operator>>(BigInteger, int);

    BigInteger &operator+();

    BigInteger &operator++();
    BigInteger operator++(int);

    BigInteger operator-() const;

    BigInteger &operator--();
    BigInteger operator--(int);



    BigInteger bin_division(const BigInteger &X);
    BigInteger division_on_small_num(const BigInteger &X);
    BigInteger bin_mod(const BigInteger &X);
    BigInteger mod_on_small_num(const BigInteger &X);
    BigInteger add_num_with_same_sign(const BigInteger &);

    BigInteger substract_with_same_sign(const BigInteger &);

    BigInteger mult_two_long(const BigInteger &);

    BigInteger &operator=(const BigInteger &);
    BigInteger &operator=(const std::string &);

    BigInteger &operator=(BigInteger &&) noexcept;

    bool abs_cmp(const BigInteger &X);

    bool get_sign() const { return sign_; }

    size_t get_size() const { return size_; }

    friend std::string to_string(const BigInteger &X);
};

bool operator>(const BigInteger &x1, const BigInteger &x2);

bool operator>=(const BigInteger &x1, const BigInteger &x2);

bool operator==(const BigInteger &x1, const BigInteger &x2);

bool operator!=(const BigInteger &x1, const BigInteger &x2);

bool operator<=(const BigInteger &x1, const BigInteger &x2);

bool operator<(const BigInteger &x1, const BigInteger &x2);

std::ostream& operator<<(std::ostream& out, const BigInteger& X);

