#include<iostream>

#include "./headers/LEXER.hpp"

class REPL{
private:
    Lexer mainLexer;
    std::string inputBuffer;
public:
    REPL(Lexer& L) {
        mainLexer = L;
    }

    void evalLoop(){
        while(true){
            std::cout<<"db engine : ";
            std::getline(std::cin , inputBuffer);
            std::cout<<"\033c";
            mainLexer.handle(inputBuffer);
        }
    }
};

int main(){
    Lexer l;
    REPL mainREPL(l);
    mainREPL.evalLoop();
    return 0;
}
