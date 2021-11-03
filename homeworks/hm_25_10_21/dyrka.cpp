#include <iostream>

int main(){
    const int N = 40;
    int Arr[N], sum = 0, dyrka;
    std::cin >> dyrka; //для проверки самостоятельно удаляем число из последовательности
    for(int i = 0; i < N; ++i){
        Arr[i] = i < dyrka ? i : i + 1;
        std::cout<<Arr[i] << ' ';
    }
  
  //вычисление дырки
    for(int i = 0; i < N; ++i){
        sum += Arr[i];
    }
    std::cout << '\n' << N + N*(N-1)/2 - sum;
}
