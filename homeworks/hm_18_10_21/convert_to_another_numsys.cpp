#include <iostream>

int main(){
    char hextable[] = {'0', '1', '2','3','4','5', '6', '7', '8', '9','A', 'B','C','D','E','F'};
    std::string answ;
    int x = -1, n = -1;
    while(x < 0){
    std::cout << "Enter the positive number, that you want to convert to another number system: ";
    std::cin >> x;}
    while(n < 2 || n > 16) {
        std::cout << "Enter the number system: ";
        std::cin >> n;
    }
    while(x > 0) {
        answ += hextable[x % n];
        x /= n;
    }
    std::reverse(answ.begin(), answ.end());
    std::cout<<"Your number in \"" << n << "\" number system is " << answ;

}
