#include <iostream>

int sqrsum(int floor){
    return (2*floor + 1) * (floor + 1) * floor / 6;
}
int start_floor(int floor){
    return (floor)*(floor -1) / 2 + 1;

}
int main(){
    int N, floor = 1;
    do{
        std::cout<<"Enter the room number: ";
        std::cin >> N;
    } while(N < 1);

    while(sqrsum(floor) < N){
        ++floor;
    }
    N -= sqrsum(floor - 1);
    int the_actual_floor = start_floor(floor);
    for(int i = 1; i <= floor; ++i){
        if(N <= floor * i){
            the_actual_floor += (i - 1);
            break;
        }
    }
    N %= floor;
    N = N == 0 ? floor:N;
    std::cout << "The floor = " << the_actual_floor << ", the room number, counting from left = " << N;
}
