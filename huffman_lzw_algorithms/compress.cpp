#include <iostream>
#include "huffman.h"
#include "lzw.h"

int main(int argc, char **argv) {
    ibitfstream x;
    obitfstream y;
    std::string str = argv[1];
    if(argc < 4){
        if(str == "-help" || str == "-?"){
            std::cout << "Use compress -lzw/-h input output for compression" << std::endl;
            std::cout << "Use compress -d input output for decompression" << std::endl;
            return 0;
        }
        else{
            std::cout << "Bad arguments, use -? for help";
            return -1;
        }
    }
    x.open(argv[2], std::ios_base::binary);
    if(!x){
        std::cout << "Wrong name for input file";
        x.close();
        return -1;
    }
    y.open(argv[3], std::ios_base::binary);
    if(!y){
        std::cout << "Wrong name for output file";
        x.close();
        y.close();
        return -1;
    }

    if(str == "-d"){
        if((char)x.peek() == 'h'){
            x.seekg(0);
            huffman_method::decompress(x, y);
            x.close();
            y.close();
            return 0;
        }
        else if(x.peek() == 'l'){
            x.seekg(0);
            lzw_method::decompress(x,y);
            x.close();
            y.close();
            return 0;
        }
        else{
            std::cout << "Wrong file for decompression";
            x.close();
            y.close();
            return -1;
        }
    }

    if(str == "-huffman"){
        huffman_method::compress(x,y);
        x.close();
        y.close();
        std::cout << "done huffman";
        return 0;
    }
    else if(str == "-lzw"){
        lzw_method::compress(x,y);
        x.close();
        y.close();
        return 0;
    }
    else{
        std::cout << "Bad arguments, use -? for help" << argc;
        x.close();
        y.close();
        return -1;
    }

}
