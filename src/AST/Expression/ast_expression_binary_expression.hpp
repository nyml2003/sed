//
// Created by venty on 2024/3/17.
//

#ifndef SED_AST_EXPRESSION_BINARY_EXPRESSION_HPP
#define SED_AST_EXPRESSION_BINARY_EXPRESSION_HPP
#include "ast_expression_base.hpp"
#include "ast_expression_operator.hpp"
namespace Compiler::AST::Expression {
    struct BinaryExpression : public Base {
        explicit BinaryExpression(Operator op, Base* left, Base* right);
        void toMermaid() override;
        void toLLVM() override;
        void analyze() override;
        EXPRESSION_TYPE getType() override;
        Base* getValue() override;
        Operator op;
        Base* left;
        Base* right;
    };
}

#endif //SED_AST_EXPRESSION_BINARY_EXPRESSION_HPP
