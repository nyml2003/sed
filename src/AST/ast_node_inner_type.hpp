//
// Created by venty on 2024/3/17.
//

#ifndef SED_AST_NODE_INNER_TYPE_HPP
#define SED_AST_NODE_INNER_TYPE_HPP
#include <vector>
#include <string>
namespace Compiler::AST {
    enum class InnerType
    {
        INT,
        VOID,
        FLOAT
    };
    inline std::vector<std::string> innerType = {"int", "void", "float"};
}
#endif //SED_AST_NODE_INNER_TYPE_HPP
