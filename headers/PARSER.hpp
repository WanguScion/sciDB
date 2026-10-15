#pragma once

#include <vector>
#include <iostream>

#include "NODES.hpp"
#include "TOKENS.hpp"
#include "AST.hpp"

enum class PARSER_STATUS{
        PARSER_FAIL,
        PARSER_SUCCESS
    };

//parsing - making sense from tokens
class Parser{
private:
    AST syntaxTree;

    PARSER_STATUS expect(std::vector<TOKEN>::iterator& it, TOKEN_SET tType){
        if(it->tokenType != tType) return throwParserError(*it);

        it++;
        return PARSER_STATUS::PARSER_SUCCESS;
    }

    PARSER_STATUS parseCreateTable(std::vector<TOKEN>& tokenList){
        //function for create table, takes reference to token stream, creates AST.
        auto it = tokenList.begin();

        expect(it, TOKEN_SET::TOKEN_CREATE);
        expect(it, TOKEN_SET::TOKEN_TABLE);
        syntaxTree.createAST(AST_NODE());

        return PARSER_STATUS::PARSER_SUCCESS;
    }

    PARSER_STATUS parseCreateDatabase(std::vector<TOKEN>& tokenList){
        //
    }

    PARSER_STATUS throwParserError(TOKEN& t){
        std::cout<<"SYNTAX ERROR : UNEXPECTED TOKEN -> <"<<t.value<<"> !"<<std::endl;
        return PARSER_STATUS::PARSER_FAIL;
    }

public:
    Parser() {}

    PARSER_STATUS parse(std::vector<TOKEN>& tokenList){
        //check the initial sequence to initiate the parsing
        auto it = tokenList.begin();

        switch(it->tokenType){
            case TOKEN_SET::TOKEN_CREATE:
                ++it;
                if(it->tokenType == TOKEN_SET::TOKEN_TABLE)     return parseCreateTable(tokenList);
                else if(it->tokenType == TOKEN_SET::TOKEN_DB)   return parseCreateDatabase(tokenList);
                else return throwParserError(*(it));
                break;
            case TOKEN_SET::TOKEN_INSERT:
                break;
            default:
                throwParserError();
                return PARSER_STATUS::PARSER_FAIL;
        }

        return PARSER_STATUS::PARSER_SUCCESS;
    }
};
