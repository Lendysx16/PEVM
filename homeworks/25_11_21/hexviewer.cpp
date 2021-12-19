#include <iostream>
#include <fstream>

std::string to_hex(unsigned char sym);
std::string to_hex(unsigned int sym);
void reverse_string(std::string &str);
unsigned int len_of_num(int k);

const char hextable[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D','E', 'F'};


int main() {
    char infilename[] = "input.txt", outfilename[] = "output.txt";
    std::ifstream InFile;
    std::ofstream OutFile;
    InFile.open(infilename, std::ios_base::binary);
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
    unsigned char buffer[16];
    size_t buffer_size = 16;

    unsigned symbols_count = 0, k = 0;

    while(InFile.peek() != EOF){

        for(size_t i = 0; i < 16; ++i){
            if(InFile.peek() != EOF){
                buffer[i] = (char)InFile.get();
            }
            else{
                symbols_count = i;
                break;
            }
        }

        if(symbols_count > 0){
            buffer_size = symbols_count;
        }
        k += 16;
        OutFile << to_hex(k) << ":";
        for(size_t i = 0; i < buffer_size; ++i){
            if(i == 7){
                OutFile << "| ";
            }
            if(buffer[i] > 32){
                OutFile<< to_hex(buffer[i]) << ' ';
            }
            else OutFile << "00" << ' ';
        }
        if(buffer_size < 8) OutFile << "  ";
        for(size_t i = 16; i > buffer_size; --i){
            OutFile <<"   ";
        }
        OutFile << "    ";
        for(size_t i = 0; i < buffer_size; ++i){
            if(buffer[i] > 32) OutFile << buffer[i];
            else OutFile << '.';
        }
        OutFile << '\n';
    }

    InFile.close();
    OutFile.close();
    return 0;
}




std::string to_hex(unsigned char sym){
    unsigned int code = sym;
    std::string answ;
    while(code > 0){
        answ += hextable[code % 16];
        code >>= 4;
    }
    std::swap(answ[0], answ[1]);
    return answ;
}
std::string to_hex(unsigned int k){
    std::string answ = "";
    while(k > 0){
        answ += hextable[k%16];
        k >>=4;
    }
    while(answ.length() < 7) answ += '0';
    reverse_string(answ);
    return answ;
}

void reverse_string(std::string &str){
    size_t len = str.length();
    --len;
    for(unsigned int i = 0; i < (len + 1)/2; ++i){
        std::swap(str[i], str[len - i]);
    }
}

unsigned int len_of_num(int k){
    if (k == 0) return 1;
    unsigned int counter = 0;
    if(k < 0) ++counter;
    while(k > 0){
        ++counter;
        k /= 10;
    }
    return counter;
}
