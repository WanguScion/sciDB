#pragma once

#include <string>
#include <vector>

enum class NODE_SET{
    NODE_COMMAND_CREATE_TABLE,
    NODE_COMMAND_CREATE_DB,

    NODE_COMMAND_INSERT,

    NODE_ID,
    NODE_SCHEMA,
    NODE_COLUMN,
    NODE_CONSTRAINT_SET,
    NODE_CONSTRAINT
};

struct AST_NODE{
    NODE_SET nodeType;
    std::string value;

    std::vector<AST_NODE*> children;
};
