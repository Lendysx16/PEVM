/*Задача на ссиракузскую последовательность*/

#include <iostream>

int main() {
    int num, max = -1, amount = 0;
    std::cout << "Enter the positive num: ";
    std::cin >> num;
    do {
        max = num > max ? num : max;
        num = num % 2 == 0 ? num / 2 : num * 3 + 1;
        ++amount;
    }while (num != 1);
    std::cout << "Top = " << max << ";\t"<< "Number of steps = " << amount << ";\n";
    
}
