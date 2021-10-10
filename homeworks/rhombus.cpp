#include <iostream>

int main()
{
    int c = 1;
    while(c != -1){
        std::cout << "Number of rows:(>1 and <30) ";
        std::cin >> c;
        if(c == -1) break;
        int count;
        std::cout << "Number of rhombuses: ";
        std::cin >> count;
        if(c < 1 || c > 30) continue;
        int spaces = c - 1;
        for(int j = 1; j <=c; ++j){
            for(int x =0; x < count; ++x){
            for(int i = spaces; i >0; --i){
                std::cout << ' ';
            }
            for(int i = 0; i < 2*j -1; ++i){
                std::cout <<'*';
            }
                for(int i = spaces; i >0; --i){
                    std::cout<<' ';
                }

            }
            --spaces;
        std::cout<<'\n';}
        spaces = 1;
        for(int j = c-1; j >=0; --j){
            for(int x =0; x < count; ++x){
            for(int i = 0; i < spaces; ++i){
                std::cout<<' ';
            }
            for(int i = 2*j-1; i > 0; --i){
                std::cout <<'*';
            }
                for(int i = 0; i < spaces; ++i){
                    std::cout<<' ';
                }
            }
            ++spaces;
            std::cout<<'\n';}
    }

}
