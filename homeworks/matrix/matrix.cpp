#include <iostream>

double** CreateMatrix(size_t rows, size_t cols);
void RandomMatrix(double** matrix, size_t rows, size_t cols);
void PrintMatrix(double** matrix, size_t rows, size_t cols);
double DetMatrix(double** matrix, size_t rows);
double** CopyMatrix(double** matrix,size_t rows, size_t cols);
void DeleteMatrix(double** matrix, size_t rows);
double** MinorMatrix(double** matrix, size_t rows, size_t nr, size_t nk);
double** InverseMatrix(double** M, size_t rows);
int main(){
    std::cout.precision(2);
    size_t rows = 3;
    auto** R = CreateMatrix(rows, rows);
    for(size_t i = 0; i < rows; ++i){
        R[i][i] = 1;
    }
    PrintMatrix(R, rows, rows);
    std::cout << DetMatrix(R, rows) << std::endl;
    PrintMatrix(InverseMatrix(R, rows), rows, rows);
    DeleteMatrix(R, rows);
}




double** CreateMatrix(size_t rows, size_t cols){
    auto** matrix = new double*[rows];
    for(size_t i = 0; i < rows; ++i){
        matrix[i] = new double[cols];
    }
    for(size_t i = 0; i < rows; ++i){
        for(size_t j = 0; j < cols; ++j){
            matrix[i][j] = 0;
        }
    }
    return matrix;
}

void RandomMatrix(double** matrix, size_t rows, size_t cols){
    for(size_t i = 0; i < rows; ++i){
        for(size_t j = 0; j < cols; ++j){
            matrix[i][j] = rand() % 10;
        }
    }
}

void PrintMatrix(double** matrix, size_t rows, size_t cols){
    for(size_t i = 0; i < rows; ++i){
        for(size_t j = 0; j < cols; ++j){
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}
double** CopyMatrix(double** matrix,size_t rows, size_t cols){
    auto** new_matrix = new double*[rows];
    for(size_t i = 0; i < rows; ++i){
        new_matrix[i] = new double[cols];
    }
    for(size_t i = 0; i < rows; ++i){
        for(size_t j = 0; j < cols; ++j){
            new_matrix[i][j] = matrix[i][j];
        }
    }
    return new_matrix;
}

void DeleteMatrix(double** matrix, size_t rows){
    for(size_t i = 0; i < rows; ++i){
        delete matrix[i];
    }
    delete matrix;
}

double DetMatrix(double** matrix, size_t rows){
        double** A = CopyMatrix(matrix, rows, rows);
        int sign = 0;
        double mult;
        for (size_t k = 0; k < rows-1; ++k) {
            int count = 1;
            if(!A[k][k]){
               while(k+count < rows){
                    if(A[k+count][k] != 0)
                        break;
                    ++count;
                }
                if(k + count == rows)
                    return 0;

                std::swap(A[k], A[k+count]);
                ++sign;
            }
            for(size_t j = k+1; j < rows; ++j){
                mult = A[j][k];
                for(size_t i = k; i < rows; ++i){
                    A[j][i] = A[j][i] - A[k][i]*mult/A[k][k];
                }
            }
        }

        double det = 1;
        for (size_t i = 0; i < rows; ++i) det *= A[i][i];

        DeleteMatrix(A, rows);

        if (sign % 2 == 1) det = -det;
        return det;

}

double** MinorMatrix(double** matrix, size_t rows, size_t nr, size_t nk) {

    double ** minor = CreateMatrix(rows - 1, rows - 1);
    int r = 0, c;
    for(size_t i = 0; i < rows; ++i){
        c = 0;
        if(i == nr) continue;
        for(size_t j = 0; j < rows; ++j){
            if (j == nk) continue;
            minor[r][c] = matrix[i][j];
            ++c;
        }
        ++r;
    }
    return minor;
}

double** InverseMatrix(double** M, size_t rows)
{
    double** A = CreateMatrix(rows, rows);
    double det = DetMatrix(M, rows);
    if (det == 0)
    {
        std::cout << "Can not find inverse matrix" ;
        return nullptr;
    }
    for (size_t i = 0; i < rows; ++i){
        for (size_t j = 0; j < rows; ++j){
            double** B = MinorMatrix(M, rows, j, i);
            A[i][j] = double(DetMatrix(B, rows - 1)) / det;
            DetMatrix(B, rows - 1);
            if ((i + j) % 2)
            {
                if(A[i][j] != 0) A[i][j] *= -1;
            }
            if(A[i][j] == 0){
                A[i][j] = 0;
            }
        }
    }
    return A;
}
