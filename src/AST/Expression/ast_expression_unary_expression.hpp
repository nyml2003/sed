//
// Created by venty on 2024/3/17.
//

#ifndef SED_AST_EXPRESSION_UNARY_EXPRESSION_HPP
#define SED_AST_EXPRESSION_UNARY_EXPRESSION_HPP
#include "ast_expression_base.hpp"
#include "ast_expression_operator.hpp"
namespace Compiler::AST::Expression {
    struct UnaryExpression : public Base {
        explicit UnaryExpression(Operator op, Base* expression);
        void toMermaid() override;
        void toLLVM() override;
        void analyze() override;
        EXPRESSION_TYPE getType() override;
        Base* getValue() override;
        Operator op;
        Base* expression;
    };
}

#endif //SED_AST_EXPRESSION_UNARY_EXPRESSION_HPP
