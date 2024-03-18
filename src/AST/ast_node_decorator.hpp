//
// Created by venty on 2024/3/17.
//

#ifndef SED_AST_NODE_DECORATOR_HPP
#define SED_AST_NODE_DECORATOR_HPP
#include <vector>
namespace Compiler::AST {
    enum class Decorator
    {
        CONSTANT,
    };
    inline std::vector<std::string> decoratorName = {"const"};
}
#endif //SED_AST_NODE_DECORATOR_HPP
