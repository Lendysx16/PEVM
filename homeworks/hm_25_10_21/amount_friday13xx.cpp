#include <iostream>

int main(){
    int d, day = 13, amount = 0;
    for(int year = 1901; year <  2001; ++year){
        for(int month = 1; month <=12; ++month){
            int a = (14 - month) / 12, m = (month + 12 * a - 2), y;
            y = year - a;
            d = (day + y + y/4 + y/400 - y/100 + 31*m/12) % 7;
            if (d == 5) {
                std::cout << "Year = " << year << "\t Month = " << month <<'\n';
                ++amount;
            }
        }
    }
    std::cout << amount;
}
