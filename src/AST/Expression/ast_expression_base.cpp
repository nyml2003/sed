//
// Created by venty on 2024/3/17.
//

#include "ast_expression_base.hpp"

namespace Compiler::AST::Expression
{
    Base::Base()
    {
        nodeType = NODE_TYPE::EXPRESSION;
    }
}