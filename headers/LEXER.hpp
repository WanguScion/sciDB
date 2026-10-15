#pragma once

#include <cctype>
#include <cmath>
#include <string>
#include <vector>
#include <iostream>

#include "TOKENS.hpp"

#define NULL_CHAR '\0'

//lexing - making tokens from the input string
class Lexer{
private:
    int cursor;
    int length;
    std::string inputCpy;
    char current;

    std::vector<TOKEN> tokenList;

    void initialize(const std::string& input){
        cursor = 0;
        length = input.size();
        inputCpy = input;
        current = inputCpy[cursor];
    }

    char advance(){
        if(cursor >= length-1){
            return NULL_CHAR;
        }
        return inputCpy[++cursor];
    }

    void skipLeadingWhitespaces(){
        // skip leading whitespaces
        while((current == ' ' || current == '\t') && current != NULL_CHAR){
            current = advance();
        }
    }

    void assignToken(TOKEN& t, const std::string& buf, bool isDigit){
        t.value = buf;

        if(buf == "create" || buf == "CREATE")              t.tokenType = TOKEN_SET::TOKEN_CREATE;
        else if(buf == "db" || buf == "DB")                 t.tokenType = TOKEN_SET::TOKEN_DB;
        else if(buf == "table" || buf == "TABLE")           t.tokenType = TOKEN_SET::TOKEN_TABLE;

        else if(buf == "insert" || buf == "INSERT")         t.tokenType = TOKEN_SET::TOKEN_INSERT;
        else if(buf == "in" || buf == "IN")                 t.tokenType = TOKEN_SET::TOKEN_IN;
        else if(buf == "values" || buf == "VALUES")         t.tokenType = TOKEN_SET::TOKEN_VALUES;

        else if(buf == "int" || buf == "INT")               t.tokenType = TOKEN_SET::TOKEN_TYPE_INT;
        else if(buf == "varchar" || buf == "VARCHAR")       t.tokenType = TOKEN_SET::TOKEN_TYPE_VARCHAR;

        else if(buf == "primarykey" || buf == "PRIMARYKEY") t.tokenType = TOKEN_SET::TOKEN_CONSTRAINT_PRIMARYKEY;

        else if(buf == "(") t.tokenType = TOKEN_SET::TOKEN_LEFT_PARENTHESES;
        else if(buf == ")") t.tokenType = TOKEN_SET::TOKEN_RIGHT_PARENTHESES;
        else if(buf == "[") t.tokenType = TOKEN_SET::TOKEN_LEFTSQBRACKET;
        else if(buf == "]") t.tokenType = TOKEN_SET::TOKEN_RIGHTSQBRACKET;
        else if(buf == ",") t.tokenType = TOKEN_SET::TOKEN_COMMA;

        else{
            if(isDigit){
                t.tokenType = TOKEN_SET::TOKEN_INT_VALUE;       //full integer value
            }else{
                t.tokenType = TOKEN_SET::TOKEN_STRING_VALUE;    //regular string
            }
        }
    }

    void delimiterWS(TOKEN& t, std::string& buf, bool isDigit){
        if(!buf.empty()){
            assignToken(t, buf, isDigit);
            tokenList.push_back(t);
        }
        buf.clear();
    }

    void delimiterSpecial(TOKEN& t, std::string& buf, bool isDigit){
        if(!buf.empty()){
            assignToken(t, buf, isDigit);
            tokenList.push_back(t);
        }
        buf.clear();

        assignToken(t, std::string(1, current), isDigit);
        tokenList.push_back(t);
    }

    void tokenize(const std::string& input){
        // writing own tokenizer from scatch, zero references less gooooooo
        std::string stringBuffer;
        TOKEN tokenBuffer;
        bool isDigit = true;

        // start tokenization, assuming token delimiter is ws, and query delimiter is NULL_CHAR
        skipLeadingWhitespaces();
        while(current != NULL_CHAR){
            switch(current){
                case ' '    :
                case '\t'   :
                    delimiterWS(tokenBuffer, stringBuffer, isDigit);
                    skipLeadingWhitespaces();
                    isDigit = true;
                    break;

                case '('    :
                case ')'    :
                case '['    :
                case ']'    :
                case ','    :
                    delimiterSpecial(tokenBuffer, stringBuffer, isDigit);
                    current = advance();
                    isDigit = true;
                    break;

                default:
                    if(!std::isdigit(current)) isDigit = false;
                    stringBuffer.push_back(current);
                    current = advance();
            }
        }

        //last token lexing, before encountering the null char :-
        delimiterWS(tokenBuffer, stringBuffer, isDigit);
    }

//     void displayAllTokens(){
//         for(size_t i=1; i<tokenList.size(); i++){
//             std::cout<<i<<") "<<tokenList[i].value;
//             std::cout<<std::endl;
//         }
//     }

public:
    Lexer() {}

    void handle(const std::string& input){
        initialize(input);
        tokenize(input);
        // displayAllTokens();
    }

    std::vector<TOKEN>& getTokenList(){
        return tokenList;
    }

    void dropTokenList(){
//         tokenList.clear();
    }
};
