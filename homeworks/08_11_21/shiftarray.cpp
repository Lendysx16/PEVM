#include <iostream>

template <typename T>
void reverse_array(T *arr, unsigned int start, unsigned int end){
    --start;
    --end;
    unsigned n = 0;
    for(unsigned int i = start; i < start + ((end - start + 1))/2; ++i){
        std::swap(arr[i], arr[end - n]);
        ++n;
    }
}

template <typename T>
void shiftArray(T *arr, int len, int shift){

    if (shift < 0){
        shift = -shift % len;
        shift = len - shift;

    }
    else shift %= len;

    if(shift){
        reverse_array(arr, 1, shift);
        reverse_array(arr, shift + 1, len);
        reverse_array(arr, 1, len);
    }
}


int main(){
    int len = 20, *R = new int[len];
    for(int i = 0; i < len; ++i){
        R[i] = i + 1;
    }

    int shift;
    std::cout<<"Enter number of elements to be shifted: ";
    std::cin >> shift;

    shiftArray(R, len, shift);

    for(int i = 0; i < len; ++i){
        std::cout << R[i] << ' ';
    }
}
