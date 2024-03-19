//
// Created by venty on 2024/3/17.
//

#ifndef SED_AST_NODE_DEFINITION_HPP
#define SED_AST_NODE_DEFINITION_HPP
#include "ast_node_base.hpp"
#include "Expression/ast_expression_base.hpp"
#include <vector>
namespace Compiler::AST{
    struct Definition : public Base {
        explicit Definition(Expression::Base *leftValue, Expression::Base *initialValue);
        explicit Definition(Expression::Base *leftValue);
        void toMermaid() override;
        void toLLVM() override;
        void analyze() override;
        Expression::Base* leftValue;
        Expression::Base* initialValue;
    };
}
#endif //SED_AST_NODE_DEFINITION_HPP
