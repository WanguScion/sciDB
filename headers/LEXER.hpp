#pragma once

#include <cctype>
#include <string>
#include <vector>
#include <iostream>

#include "TOKENS.hpp"

#define NULL_CHAR '\0'

struct TOKEN{
    TOKEN_SET tokenType;
    std::string value;
};

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

    void skipLeadingWhitespaces(){
        // skip leading whitespaces
        while((current == ' ' || current == '\t') && current != NULL_CHAR){
            current = advance();
        }
    }

    char advance(){
        if(cursor >= length-1){
            return NULL_CHAR;
        }
        return inputCpy[++cursor];
    }

    void assignToken(TOKEN& t, const std::string& buf){
        t.value = buf;

        if(buf == "create" || buf == "CREATE")          t.tokenType = TOKEN_SET::TOKEN_CREATE;
        else if(buf == "new" || buf == "NEW")           t.tokenType = TOKEN_SET::TOKEN_NEW;
        else if(buf == "db" || buf == "DB")             t.tokenType = TOKEN_SET::TOKEN_DB;
        else if(buf == "table" || buf == "TABLE")       t.tokenType = TOKEN_SET::TOKEN_TABLE;
        else if(buf == "insert" || buf == "INSERT")     t.tokenType = TOKEN_SET::TOKEN_INSERT;
        else if(buf == "in" || buf == "IN")         t.tokenType = TOKEN_SET::TOKEN_IN;
        else if(buf == "values" || buf == "VALUES")     t.tokenType = TOKEN_SET::TOKEN_VALUES;

        else if(buf == "(")  t.tokenType = TOKEN_SET::TOKEN_LEFT_PARENTHESES;
        else if(buf == ")")  t.tokenType = TOKEN_SET::TOKEN_RIGHT_PARENTHESES;
        else if(buf == "\"")  t.tokenType = TOKEN_SET::TOKEN_DBLQUOTES;

        else t.tokenType = TOKEN_SET::TOKEN_STRING; //regular string
    }

    void tokenize(const std::string& input){
        // writing own tokenizer from scatch, zero references less gooooooo
        std::string stringBuffer;
        TOKEN tokenBuffer;

        skipLeadingWhitespaces();

        // start tokenization, assuming token delimiter is ws, and query delimiter is NULL_CHAR
        while(current != NULL_CHAR){
            if(current == ' '){
                assignToken(tokenBuffer, stringBuffer);
                tokenList.push_back(tokenBuffer);
                stringBuffer.clear();
            }
            else if(current == '('){
                assignToken(tokenBuffer, stringBuffer);
                tokenList.push_back(tokenBuffer);
                assignToken(tokenBuffer, "(");
                tokenList.push_back(tokenBuffer);
                stringBuffer.clear();
            }
            else if(current == '['){
                assignToken(tokenBuffer, stringBuffer);
                tokenList.push_back(tokenBuffer);
                assignToken(tokenBuffer, "[");
                tokenList.push_back(tokenBuffer);
                stringBuffer.clear();
            }
            else{
                stringBuffer.push_back(current);
            }

            current = advance();
        }
        //last token lexing, before encountering the null char :-
        assignToken(tokenBuffer, stringBuffer);
        tokenList.push_back(tokenBuffer);
        stringBuffer.clear();
    }

    void displayAllTokens(){
        for(size_t i=0; i<tokenList.size(); i++){
            std::cout<<i<<") "<<tokenList[i].value<<std::endl;
        }
    }

    void dropList(){
        tokenList.clear();
    }

public:
    Lexer() {}

    void handle(const std::string& input){
        initialize(input);
        tokenize(input);
        displayAllTokens();
        dropList();
    }
};
