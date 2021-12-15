#include <iostream>
#include <fstream>

int main() {
    char infilename[] = "input.txt", outfilename[] = "output.txt";
    std::ifstream InFile;
    std::ofstream OutFile;
    InFile.open(infilename);
    if(!InFile){
        std::cout<< "Can not open input file";
        return 1;
    }
    OutFile.open(outfilename);
    if(!OutFile){
        std::cout << "Can not open output file";
        InFile.close();
        return 2;
    }
    


    InFile.close();
    OutFile.close();
    return 0;
}
