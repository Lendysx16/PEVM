#include "boolexpr.h"


bool Fullsystem::check_for(criterion crt, BooleanExpression &func) {
    switch (crt) {
        case T0:
            return check_for_T0(func);
        case T1:
            return check_for_T1(func);
        case M:
            return check_for_M(func);
        case S:
            return check_for_S(func);
        case L:
            return check_for_L(func);
        default:
            return false;
    }

}

bool Fullsystem::isFullSystem(Fullsystem &sys) {
    std::vector<criterion> vector_of_criterions;
    vector_of_criterions.push_back(T0);
    vector_of_criterions.push_back(T1);
    vector_of_criterions.push_back(M);
    vector_of_criterions.push_back(S);
    vector_of_criterions.push_back(L);
    for (auto element: vector_of_criterions) {
        if (sys.Posts_table.find(element) == sys.Posts_table.end())
            for (auto &func: sys.systems) {
                auto res = check_for(element, func);
                if (res) {
                    sys.Posts_table.insert(element);
                    break;
                }
            }
        if (sys.Posts_table.find(element) == sys.Posts_table.end())
            return false;
    }
    return true;
}


bool Fullsystem::check_for_T0(BooleanExpression &expr) {
    if (!expr.table.bits[0]) {
        return false;
    }
    return true;
}

bool Fullsystem::check_for_T1(BooleanExpression &expr) {
    if (expr.table.bits[expr.table.size_of_array - 1]) {
        return false;
    }
    return true;
}

bool Fullsystem::check_for_L(BooleanExpression &expr) {
    auto k = expr.zhegalkin_str();
    delete[] k;
    return !expr.is_lineal;
}

bool Fullsystem::check_for_S(BooleanExpression &expr) {
    auto result = expr.table.bits;
    auto size = expr.table.size_of_array;
    for (auto i = 0; i < size / 2; ++i) {
        if (result[i] == result[size - i - 1]) {
            result = nullptr;
            delete[] result;
            return true;
        }
    }
    result = nullptr;
    delete[] result;
    return false;

}

bool Fullsystem::check_for_M(BooleanExpression &expr) {
    auto result = expr.table.bits;
    auto size = expr.table.size_of_array;
    int shift = (int) size;
    if ((shift - 1) & shift) {
        return false;
    }
    while ((shift /= 2) > 0) {
        int i = 0;
        while (i < size) {
            for (int j = shift; j--; ++i)
                if (result[i] > result[i + shift]) {
                    result = nullptr;
                    delete[] result;
                    return true;
                }
        }
        i += shift;
    }

    result = nullptr;
    delete[] result;
    return false;
}





