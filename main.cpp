#include<iostream>

#include "./headers/LEXER.hpp"
#include "./headers/PARSER.hpp"

class REPL{
private:
    Lexer mainLexer;
    Parser mainParser;
    std::string inputBuffer;
public:
    REPL(Lexer& L, Parser& P) {
        mainLexer = L;
        mainParser = P;
    }

    void evalLoop(){
        while(true){
            std::cout<<"db engine : ";
            std::getline(std::cin , inputBuffer);
            std::cout<<"\033c";
            mainLexer.handle(inputBuffer);
            mainParser.parse(mainLexer.getTokenList());
            mainLexer.dropTokenList();
        }
    }
};

int main(){
    Lexer l;
    Parser p;

    REPL mainREPL(l, p);

    mainREPL.evalLoop();
    return 0;
}
