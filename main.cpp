#include<iostream>

#include "./headers/LEXER.hpp"

class REPL{
private:
    Lexer mainLexer;
    std::string inputBuffer;
public:
    REPL(Lexer& L) {
        mainLexer = L;
        evalLoop();
    }
    void evalLoop(){
        while(true){
            std::cout<<"db engine : ";
            std::getline(std::cin , inputBuffer);
            mainLexer.handle(inputBuffer);
        }
    }
};

int main(){
    Lexer l;
    REPL mainREPL(l);
    return 0;
}
