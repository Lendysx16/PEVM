#include "boolexpr.h"


BooleanExpression::set_of_bits::set_of_bits(unsigned int num) {
    if (bits != nullptr) delete[] bits;
    size_of_array = num;
    bits = new bool[num];
    null();
}

BooleanExpression::set_of_bits &BooleanExpression::set_of_bits::operator++() {
    for (int i = (int)size_of_array - 1; i > -1; --i) {
        bits[i] ^= 1;
        if (bits[i] == 1) break;
    }
    return *this;
}

BooleanExpression::function_result::function_result(unsigned int num) {
    if (bits != nullptr) delete[] bits;
    size_of_array = 1 << num;
    bits = new bool[num];
}

BooleanExpression::function_result &BooleanExpression::function_result::operator=(const function_result &X) {
    if (this != &X) {
        delete[] bits;
        size_of_array = X.size_of_array;
        bits = new bool[X.size_of_array];
        for (auto i = 0; i < X.size_of_array; ++i){ bits[i] = X.bits[i];
        }
    }
    return *this;
}

BooleanExpression::set_of_bits &BooleanExpression::set_of_bits::operator=(const set_of_bits &X) {
    if (this != &X) {
        delete[] bits;
        size_of_array = X.size_of_array;
        bits = new bool[X.size_of_array];
        for (auto i = 0; i < X.size_of_array; ++i) bits[i] = X.bits[i];
    }
    return *this;
}

bool help_for_infix(char ch) {
    return (ch == 'v' or ch == '|' or ch == '>' or ch == '<' or ch == '^'
            or ch == '=' or ch == '~' or ch == '+' or ch == '(' or ch == ')' or ch == '&');
}

char *BooleanExpression::InfixFilter(const char *in) {
    global::Workspace.clear();
    int size = 0;
    while (in[size] != '\0') ++size;
    auto out = new char[size];
    size = 0;
    for (auto i = 0; in[i] != '\0'; ++i) {
        if (in[i] == 'x' or in[i] == 'X') {
            out[size++] = 'x';
            ++i;
            int num = 0;
            while (in[i] != ' ' and in[i] != '\0') {
                if (help_for_infix(in[i])) break;
                num += in[i] - '0';
                ++i;
            }
            if (num > 9) throw std::invalid_argument("Invalid input file");
            out[size++] = (char) num + '0';
            if (global::Workspace.find(VariableValue((char) num + '0', false)) == nullptr){
                global::Workspace.insert(VariableValue((char) num + '0'));
            }
            if (help_for_infix(in[i])) out[size++] = in[i];
            if (in[i] == '\0') break;
        } else if (help_for_infix(in[i])) {
            out[size++] = in[i];
        } else if (in[i] == '0') {
            out[size++] = 'Z';
        } else if (in[i] == '1') {
            out[size++] = 'O';
        } else if (in[i] == '\0') break;
        else if (in[i] != ' ') throw std::invalid_argument("Invalid input file");

    }
    out[size] = '\0';
    return out;

}


const char BooleanExpression::ActionTable[][7] = {
        {0, 2, 5, 1, 2, 2, 2},
        {3, 2, 3, 1, 3, 2, 3},
        {5, 2, 4, 1, 2, 2, 2},
        {3, 2, 3, 1, 3, 2, 3},
        {3, 2, 3, 1, 2, 2, 3}
};

int BooleanExpression::ActionsRowNumber(char ch) {
    switch (ch) {
        case 0:
            return 0;
        case '&':
            return 1;
        case '(':
            return 2;
        case '~':
            return 3;
        default:
            return 4;
    }
}

int BooleanExpression::ActionsColNumber(char ch) {
    switch (ch) {
        case 0:
            return 0;
        case '(':
            return 1;
        case ')':
            return 2;
        case '&':
            return 4;
        case '~':
            return 5;
        case 'v':
            return 6;
        case '^':
            return 6;
        case '>':
            return 6;
        case '<':
            return 6;
        case '=':
            return 6;
        case '+':
            return 6;
        case '|':
            return 6;
        default:
            return 3;

    }
}

char *BooleanExpression::InfixToPostfix(const char *in) {
    auto S = std::stack<char>();
    int size = 0;
    while (in[size] != '\0') ++size;
    auto out = new char[size];
    for(auto i = 0; i < size; ++i) out[i] = '\0';
    int i = 0;
    size = 0;
    int row, col;
    char action;
    do {
        col = ActionsColNumber(in[i]);
        row = S.empty() ? 0 : ActionsRowNumber(S.top());
        action = ActionTable[row][col];
        switch (action) {
            case 0:
                out[size] = '\0';
                break;
            case 1:
                if (in[i] == 'x') {
                    out[size++] = in[i++];
                    out[size++] = in[i++];
                } else {
                    if (in[i] == 'Z' or in[i] == 'O') {
                        out[size++] = in[i++];
                    }
                }
                break;
            case 2:
                S.push(in[i]);
                ++i;
                break;
            case 3:
                out[size++] = S.top();
                S.pop();
                break;
            case 4:
                S.pop();
                ++i;
                break;
            case 5:
                throw std::invalid_argument("Error in input file");

            default:
                throw std::invalid_argument("Error in input file");
        }

    } while (action != 0);
    out[size] = '\0';
    return out;
}


AbstractNode *BooleanExpression::PostfixToTree(const char *in) {
    int size = 0, max = 0;
    if(in[0] == '\0') throw std::invalid_argument("Expression is empty");
    while(in[max] != '\0') ++max;
    std::stack<AbstractNode *> S;
    char ch, sym;
    AbstractNode *result, *left, *right;
    try {
        while ( size < max) {
            ch = in[size];
            left = right = nullptr;
            switch (ch) {
                case '&':
                    if (S.empty()) throw 1;
                    right = S.top();
                    S.pop();
                    if (S.empty()) throw 1;
                    left = S.top();
                    S.pop();
                    result = new AndNode(left, right);
                    break;
                case 'v':
                    if (S.empty()) throw 1;
                    right = S.top();
                    S.pop();
                    if (S.empty()) throw 1;
                    left = S.top();
                    S.pop();
                    result = new OrNode(left, right);
                    break;
                case '>':
                    if (S.empty()) throw 1;
                    right = S.top();
                    S.pop();
                    if (S.empty()) throw 1;
                    left = S.top();
                    S.pop();
                    result = new ImplicationNode(left, right);
                    break;
                case '<':
                    if (S.empty()) throw std::invalid_argument("Bad input file");;
                    right = S.top();
                    S.pop();
                    if (S.empty()) throw std::invalid_argument("Bad input file");;
                    left = S.top();
                    S.pop();
                    result = new rImplicationNode(left, right);
                    break;
                case '+':
                    if (S.empty()) throw std::invalid_argument("Bad input file");;
                    right = S.top();
                    S.pop();
                    if (S.empty()) throw std::invalid_argument("Bad input file");;
                    left = S.top();
                    S.pop();
                    result = new XorNode(left, right);
                    break;
                case '|':
                    if (S.empty()) throw 1;
                    right = S.top();
                    S.pop();
                    if (S.empty()) throw 1;
                    left = S.top();
                    S.pop();
                    result = new NorNode(left, right);
                    break;
                case '^':
                    if (S.empty()) throw 1;
                    right = S.top();
                    S.pop();
                    if (S.empty()) throw 1;
                    left = S.top();
                    S.pop();
                    result = new StrokeNode(left, right);
                    break;
                case '=':
                    if (S.empty()) throw 1;
                    right = S.top();
                    S.pop();
                    if (S.empty()) throw 1;
                    left = S.top();
                    S.pop();
                    result = new EqNode(left, right);
                    break;
                case '~':
                    if (S.empty()) throw 1;
                    left = S.top();
                    S.pop();
                    result = new NegationNode(left);
                    break;
                case 'O':
                    result = new ConstNode(true);
                    break;
                case 'Z':
                    result = new ConstNode(false);
                    break;
                case 'x':
                    sym = in[++size];
                    result = new VariableNode(sym);
                    break;
                default:
                    throw std::invalid_argument("Wrong input file");
            }

            S.push(result);
            if(in[size] != '\0') ++size;
        }
        if (S.size() > 1) {
            left = right = nullptr;
            throw 2;
        }
        result = S.top();
        return result;
    }
    catch (int E) {
        delete left;
        delete right;
        while (!S.empty()) {
            left = S.top();
            S.pop();
            delete left;
        }
        throw std::invalid_argument("Bad input file");
    }
}

AbstractNode *BooleanExpression::Parse(const char *in) {
    char *postfix = nullptr;
    char *filtered = nullptr;
    try {
        filtered = InfixFilter(in);
        postfix = InfixToPostfix(filtered);
        auto result = PostfixToTree(postfix);
        delete[] postfix;
        delete[] filtered;
        return result;
    }
    catch (std::invalid_argument &E) {
        delete[] postfix;
        delete[] filtered;
        throw std::invalid_argument(E.what());
    }
}


BooleanExpression::BooleanExpression(const char *in) {
    root = Parse(in);
    for(auto i = global::Workspace.begin(); i != global::Workspace.end(); ++i) {
        variables.push_back((*i).name());
    }

    number_of_variables = global::Workspace.size();
    table = function_result(number_of_variables);
    temporary_row = set_of_bits(number_of_variables);
    fill_truthtable();
}

BooleanExpression::BooleanExpression(const BooleanExpression &X) {
    root = X.root->make_node();
    number_of_variables = X.number_of_variables;
    table = X.table;
    temporary_row = X.temporary_row;
    variables = X.variables;
    is_lineal = X.is_lineal;
    fill_truthtable();
}

BooleanExpression &BooleanExpression::operator=(const BooleanExpression &X) {
    if (this != &X) {
        delete root;
        root = X.root->make_node();
        number_of_variables = X.number_of_variables;
        table = X.table;
        temporary_row = X.temporary_row;
        variables = X.variables;
        is_lineal = X.is_lineal;
    }
    return *this;
}
BooleanExpression BooleanExpression::operator=(BooleanExpression &&X)noexcept {
    if (this != &X) {
        delete root;
        root = X.root;
        number_of_variables = X.number_of_variables;
        table = X.table;
        temporary_row = X.temporary_row;
        X.temporary_row.bits = nullptr;
        X.root = nullptr;
        X.table.bits = nullptr;
        variables = X.variables;
        is_lineal = X.is_lineal;
    }
    return *this;
}

void BooleanExpression::fill_truthtable() {
    global::Workspace.clear();
    for(auto i = variables.begin(); i != variables.end(); ++i) {
        global::Workspace.insert(VariableValue(*i));
    }
    for (int i = 0; i < table.size_of_array; ++i) {
        int k = 0;
        for (auto pos = global::Workspace.begin(); pos != global::Workspace.end(); ++pos) {
            (*pos).setvalue(temporary_row.bits[k++]);
        }
        ++temporary_row;
        table.bits[i] = calc_consts();
    }
    temporary_row.null();
}

void BooleanExpression::truthtable(){
    global::Workspace.clear();
    for (int i = 0; i < number_of_variables; ++i) {
        global::Workspace.insert(variables[i]);
    }
    for (auto & pos : global::Workspace) std::cout << pos.str() << "  ";
    std::cout << "F" << std::endl;
    for (int i = 0; i < table.size_of_array; ++i) {
        for (int j = 0; j < temporary_row.size_of_array; ++j) {
            std::cout << temporary_row.bits[j] << "   ";
        }
        ++temporary_row;
        std::cout << table.bits[i] << std::endl;
    }
    temporary_row.null();
}


const char* BooleanExpression::zhegalkin_str() {
    is_lineal = true;
    global::Workspace.clear();
    for(unsigned char & variable : variables) {
        global::Workspace.insert(variable);
    }
    std::vector<std::vector<bool>> table_of_zhegalkin(table.size_of_array);
    for(int i = 0; i < table.size_of_array; ++i) {
        table_of_zhegalkin[0].push_back(table.bits[i]);
    }
    for(int i = 1; i < table.size_of_array; ++i){
        for(int j = 0; j < table.size_of_array - i; ++j){
            table_of_zhegalkin[i].push_back(table_of_zhegalkin[i-1][j] ^ table_of_zhegalkin[i-1][j+1]);
        }
    }
    auto result = new char[256];
    for(auto i = 0; i < 256; ++i){
        result[i] = '\0';
    }
    int size = 0;
    if(table_of_zhegalkin[0][0]) {
        result[size++] = '1';
        result[size++] = '+';
    }
    else{
        result[size++] = '0';
        result[size++] = '+';
    }
    temporary_row.null();
    for(int i = 1; i < table.size_of_array; ++i){
        int k = 0;
        ++temporary_row;
        if(table_of_zhegalkin[i][0] == 0) continue;
        for(int j = 0; j < temporary_row.size_of_array; ++j){
            if(temporary_row.bits[j] == 1){
                ++k;
                result[size++] = 'x';
                result[size++] = (char)variables[j];
                result[size++] = '&';
            }
            if(k > 1) is_lineal = false;
        }
        if(result[size - 1] == '&') result[size - 1] = '+';
    }
    if(result[size - 1] == '+') result[size - 1] = '\0';
    return result;
}

bool BooleanExpression::calc() const {
    global::Workspace.clear();
    int value;
    for(unsigned char variable : variables) {
        std::cout << "Enter x" << variable << ": ";
        std::cin >> value;
        global::Workspace.insert(VariableValue(variable));
        (*global::Workspace.find(variable)).setvalue(value);
    }
    return root->calc();
}

BooleanExpression BooleanExpression::zhegalkin(){
    auto k = zhegalkin_str();
    auto new_zheg = BooleanExpression(k);
    delete[] k;
    return new_zheg;
}

const char* BooleanExpression::cnf_str(){
    auto result = new char[256];
    int size = 0;
    for(auto i = 0; i < 256; ++i){
        result[i] = '\0';
    }
    temporary_row.null();
    for(auto i = 0; i < table.size_of_array; ++i){
        if(table.bits[i] == 1) {
            ++temporary_row;
            continue;
        }
        result[size++] = '(';
        for(auto j = 0; j < temporary_row.size_of_array; ++j){
            if(temporary_row.bits[j] == 0){
                result[size++] = 'x';
                result[size++] = (char)variables[j];
                result[size++] = 'v';
            }
            else{
                result[size++] = '~';
                result[size++] = 'x';
                result[size++] = (char)variables[j];
                result[size++] = 'v';
            }
        }
        ++temporary_row;
        result[size - 1] = ')';
        result[size++] = '&';
    }
    if(result[size - 1] == '&') result[size - 1] = '\0';
    if(size == 0){
        delete[] result;
        throw "Can not build CNF from constant expression";
    }
    return result;
}

const char* BooleanExpression::dnf_str(){
    auto result = new char[256];
    int size = 0;
    for(auto i = 0; i < 256; ++i){
        result[i] = '\0';
    }
    temporary_row.null();
    for(auto i = 0; i < table.size_of_array; ++i){
        if(table.bits[i] == 0) {
            ++temporary_row;
            continue;
        }
        result[size++] = '(';
        for(auto j = 0; j < temporary_row.size_of_array; ++j){
            if(temporary_row.bits[j] == 1){
                result[size++] = 'x';
                result[size++] = (char)variables[j];
                result[size++] = '&';
            }
            else{
                result[size++] = '~';
                result[size++] = 'x';
                result[size++] = (char)variables[j];
                result[size++] = '&';
            }
        }
        ++temporary_row;
        result[size - 1] = ')';
        result[size++] = 'v';
    }
    if(result[size - 1] == 'v') result[size - 1] = '\0';
    if(size == 0) {
        delete[] result;
        throw "Can not build DNF from constant expression";
    }
    return result;
}


BooleanExpression BooleanExpression::cnf() {
    auto str = cnf_str();
    auto new_cnf = BooleanExpression(str);
    delete[] str;
    return new_cnf;
}


BooleanExpression BooleanExpression::dnf() {
    auto str = dnf_str();
    auto new_dnf = BooleanExpression(str);
    delete[] str;
    return new_dnf;
}