#pragma once
#include <vector>
#include <stack>
#include "boolexprnode.h"


class BooleanExpression{
private:
    friend class Fullsystem;
    bool is_lineal = false;
struct set_of_bits{
    bool *bits = nullptr;
    unsigned int size_of_array;
    set_of_bits(unsigned int num);
    set_of_bits(){
        bits = nullptr;
        size_of_array = 0;
    }
    void null() const{
        for(auto i = 0; i < size_of_array; ++i) bits[i] = false;
    }
    ~set_of_bits(){
        delete[] bits;
    }
    set_of_bits &operator++();
    set_of_bits &operator=(const set_of_bits&);

};
struct function_result{
    unsigned int size_of_array;
    bool *bits = nullptr;
    function_result(unsigned int num);
    function_result() {
        size_of_array = 0;
        bits = nullptr;
    }

    ~function_result() {
        delete[] bits;
    }
    function_result&operator=(const function_result&);


};


    const char* zhegalkin_str();
    const char* cnf_str();
    const char* dnf_str();

    static const char ActionTable[][7];
    static int ActionsRowNumber(char ch);
    static int ActionsColNumber(char ch);
    static char* InfixFilter(const char*);
    static char* InfixToPostfix(const char*);
    static AbstractNode* PostfixToTree(const char*);
    static AbstractNode* Parse(const char* in);


    unsigned int number_of_variables;
    AbstractNode *root;
    set_of_bits temporary_row;
    function_result table;
    void fill_truthtable();
    bool calc_consts(){
        return root->calc();
    }
    std::vector<unsigned char> variables = {};
public:

    BooleanExpression(const char*);
    BooleanExpression &operator=(const BooleanExpression& X);
    BooleanExpression operator=( BooleanExpression&& X) noexcept;
    BooleanExpression(const BooleanExpression& X);

    bool calc() const;
    operator std::string() const{
        return root->str();
    }
    void truthtable() ;
    BooleanExpression zhegalkin();
    BooleanExpression cnf();
    BooleanExpression dnf();
    bool linean() const{
       return is_lineal;
     }

};




class Fullsystem {
private:
    enum criterion{
        T0,
        T1,
        M,
        S,
        L
    };
    avltree<criterion> Posts_table;
    std::vector<BooleanExpression> systems;
    static bool check_for_T0(BooleanExpression& expr);
    static bool check_for_T1(BooleanExpression& expr);
    static bool check_for_M(BooleanExpression& expr);
    static bool check_for_S(BooleanExpression& expr);
    static bool check_for_L(BooleanExpression& expr);
    static bool check_for(criterion criterion, BooleanExpression& func);

public:
    Fullsystem(const std::vector<BooleanExpression> &sys){
        for(auto &element : sys){
            systems.push_back(element);
        }
        for(auto & el: systems){
            el.fill_truthtable();
        }
    }
    static bool isFullSystem(Fullsystem& sys);

};