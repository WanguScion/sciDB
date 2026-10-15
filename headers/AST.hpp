#include "NODES.hpp"

class AST{
private:
    AST_NODE* root;

public:
    AST(){
        root = NULL;
    };

    AST(AST_NODE& r, size_t n): root(&r){}

    void insertAST(AST_NODE& n){
        //
    }
};
