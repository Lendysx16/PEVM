#include <iostream>

int main(){
    size_t rows, cols;
    std::cout <<"Enter the number of rows: ";
    std::cin >> rows;
    std::cout << "Enter the number of cols: ";
    std::cin >> cols;
    auto **R = new int*[rows];
    for(size_t i = 0; i < rows; ++i){
        R[i] = new int[cols];
    }
    for(size_t i = 0; i < rows; ++i){
        for(size_t j = 0; j < cols; ++j){
            R[i][j] = 0;
        }
    }
    size_t horiz = 1, vert = 1;
    int s = 1;

    for (int j = 0; j < cols; ++j) {
        R[0][j] = s;
        s++;
    }
    for (int i = 1; i < rows; ++i) {
        R[i][cols - 1] = s;
        s++;
    }
    for (int j = cols - 2; j > - 1; --j) {
        R[rows - 1][j] = s;
        s++;
    }
    for (int i = rows - 2; i > 0; --i) {
        R[i][0] = s;
        s++;
    }


    while(s < rows * cols){
        while(R[vert][horiz + 1] == 0){
            R[vert][horiz] = s;
            ++s;
            ++horiz;
        }
        while(R[vert + 1][horiz] == 0){
            R[vert][horiz] = s;
            ++s;
            ++vert;
        }
        while(R[vert][horiz - 1] == 0){
            R[vert][horiz] = s;
            ++s;
            --horiz;
        }
        while(R[vert - 1][horiz] == 0){
            R[vert][horiz] = s;
            ++s;
            --vert;
        }
    }
    for(size_t i = 0; i < rows; ++i){
        for(size_t j = 0; j < cols; ++j){
            if(R[i][j] == 0) R[i][j] = s;
            std::cout << R[i][j] << "\t";
        }
        std::cout << '\n';
    }
}
