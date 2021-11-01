#include <iostream>


int main(){
    const double eps = 1e-6;
    double pi1 = 0, an = 1;
    int minus = -1;
    int N = 0;
    while(an > eps){
        pi1 += an * (minus * -1);
        ++N;
        an = 1.0 /(2*N + 1);
        minus *= -1;
    }
    std::cout <<"Pi = "<< 4 * pi1 << ";\t N = " << N << ";\n\n\n";


    const int R = 100;
    double pi2 = 0;
    int circle_p = 0;
    int x,y;
    srand(time(nullptr));
    for(int i = 0; i < N; ++i){
        x = rand() % R;
        y = rand() % R;
        if(x*x + y*y <= R*R) {
            ++circle_p;
        }
    }
    pi2 = 4 * (double)circle_p / N;
    std::cout<< "Pi = " << pi2;
}
/*Из полученных данных получается, что для подсчета числа pi через разложение в ряд требуется менеьше проходов цикла*/
