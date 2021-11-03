#include <iostream>
#include <string>

int zeros(int num, bool rod = 1);
int tens(int num, bool rod = 1);
int hundred(int num, bool rod = 1);
void transform(int num);



int main(){
    srand(time(nullptr));
    int num;
    std::cout<<"Введите число: ";
    std::cin >> num;
    if(num < 0){
        std::cout << "минус ";
        num = -num;
    }
    transform(num);
    std::cout<<'\n';
}



int zeros(int num, bool rod){
    switch(num){
        case 0:
            std::cout<<"ноль ";
            break;
        case 1:{
            std::string od = rod ? "один ":"одна ";
            std::cout<<od;
            break;}
        case 2:{
            std::string dva = rod ? "два ":"две ";
            std::cout<<dva;
            break;}
        case 3:{
            std::cout<<"три ";
            break;}
        case 4:
            std::cout<<"четыре ";
            break;
        case 5:
            std::cout<<"пять ";
            break;
        case 6:
            std::cout<<"шесть ";
            break;
        case 7:
            std::cout<<"семь ";
            break;
        case 8:
            std::cout<<"восемь ";
            break;
        case 9:
            std::cout<<"девять ";
            break;
    }
    return num;
}
int tens(int num, bool rod){
    if (num == 0) {
        return 0;
    }
    switch(num){
        case 10:
            std::cout<<"десять ";
            break;
        case 11:
            std::cout<<"одиннадцать ";
            break;
        case 12:
            std::cout<<"двенадцать ";
            break;
        case 13:
            std::cout<<"тринадцать ";
            break;
        case 14:
            std::cout<<"четырнадцать ";
            break;
        case 15:
            std::cout<<"пятнадцать ";
            break;
        case 16:
            std::cout<<"шестнадцать ";
            break;
        case 17:
            std::cout<<"семнадцать ";
            break;
        case 18:
            std::cout<<"восемнадцать ";
            break;
        case 19:
            std::cout<<"девятнадцать ";
            break;
    }
    if (num >= 90){
        std::cout <<"девяносто ";
    }
    else if (num >= 80){
        std::cout <<"восемьдесят ";
    }
    else if (num >= 70){
        std::cout << "семьдесят ";
    }
    else if (num >= 60){
        std::cout << "шестьдесят ";
    }
    else if (num >= 50){
        std::cout << "пятьдесят ";
    }
    else if (num >= 40){
        std::cout << "сорок ";
    }
    else if (num >= 30){
        std::cout << "тридцать ";
    }
    else if (num >= 20){
        std::cout << "двадцать ";
    };
    if(num % 10 != 0 && num / 10 != 1){
        return zeros(num % 10, rod);
    }
    else return 0;
}
int hundred(int num, bool rod){
    if(num >= 900){
        std::cout<<"девятьсот ";
    }
    else if(num >= 800){
        std::cout<<"восемьсот ";
    }
    else if(num >= 700){
        std::cout<<"семьсот ";
    }
    else if(num >= 600){
        std::cout<<"шестьсот ";
    }
    else if(num >= 500){
        std::cout<<"пятьсот ";
    }
    else if(num >= 400){
        std::cout<<"четыреста ";
    }
    else if(num >= 300){
        std::cout<<"тристо ";
    }

    else if(num >= 200){
        std::cout<<"двести ";
    }
    else if(num >= 100){
        std::cout<<"сто ";
    };

    if(num % 100 != 0){
        return(tens(num%100, rod));
    }
    else return 0;
}

void transform(int num){
    if (num == 0){
        std::cout << "ноль ";
    }
    int numcopy = num, amount_of_digits = 0;
    while(numcopy > 0){
        numcopy /= 10;
        ++amount_of_digits;
    }
    while(amount_of_digits != 0){
        switch(amount_of_digits) {
            case 9:{
                int expression = hundred((num / 1000000));
                if (expression < 5 && expression > 1){
                    std::cout << "миллиона ";
                }
                else if (expression == 1){
                    std::cout << "миллион ";
                }
                else{
                    std::cout << "миллионов ";
                }
                num %= 1000000;
                amount_of_digits -= 3;
                break;}
            case 8:{
                int expression = hundred((num / 1000000));
                if (expression < 5 && expression > 1){
                    std::cout << "миллиона ";
                }
                else if (expression == 1){
                    std::cout << "миллион ";
                }
                else{
                    std::cout << "миллионов ";
                }
                num %= 1000000;
                amount_of_digits -= 2;
                break;}
            case 7:{
                int expression = hundred((num / 1000000));
                if (expression < 5 && expression > 1){
                    std::cout << "миллиона ";
                }
                else if (expression == 1){
                    std::cout << "миллион ";
                }
                else{
                    std::cout << "миллионов ";
                }
                num %= 1000000;
                amount_of_digits -= 1;
                break;}
            case 6:{
                if (num/1000 != 0){
                int expression = hundred((num / 1000), 0);
                if (expression < 5 && expression > 1){
                    std::cout << "тысячи ";
                }
                else if(expression == 1){
                    std::cout<<"тысяча ";
                }
                else{
                    std::cout << "тысяч ";
                }
                num %= 1000;}
                amount_of_digits -= 3;
                break;}
            case 5:{
                int expression = hundred((num / 1000), 0);
                if (expression < 5 && expression > 1){
                    std::cout << "тысячи ";
                }
                else if(expression == 1){
                    std::cout<<"тысяча ";
                }
                else{
                    std::cout << "тысяч ";
                }
                num %= 1000;
                amount_of_digits -= 2;
                break;}
            case 4:{
                int expression = hundred((num / 1000), 0);
                if (expression < 5 && expression > 1){
                    std::cout << "тысячи ";
                }
                else if(expression == 1){
                    std::cout<<"тысяча ";
                }
                else{
                    std::cout << "тысяч ";
                }
                num %= 1000;
                amount_of_digits -= 1;
                break;}
            default:{
                hundred(num);
                amount_of_digits = 0;
                break;
            }
        }
    }
}
