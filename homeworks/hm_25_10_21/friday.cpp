#include <iostream>

int main(){
    int day, month;
    std::cout << "enter the day: ";
    std::cin >> day;
    std::cout << "enter the month: ";
    std::cin >> month;
    int d = -1;
    int a = (14 - month) / 12, m = (month + 12 * a - 2), y, Year = 2020;
    while(d!=5){
        ++Year;
        y = Year - a;
        d = (day + y + y/4 + y/400 - y/100 + 31*m/12) % 7;
    }
    std::cout << Year;
}
