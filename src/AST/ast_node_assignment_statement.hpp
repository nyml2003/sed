//
// Created by DELL on 2024/3/18.
//

#ifndef SED_AST_NODE_ASSIGNMENT_STATEMENT_HPP
#define SED_AST_NODE_ASSIGNMENT_STATEMENT_HPP
#include "ast_node_base.hpp"
#include "ast_expression_base.hpp"
namespace Compiler::AST {
    struct AssignmentStatement : public Base {
        explicit AssignmentStatement(Expression::Base* leftValue, Expression::Base* expression);
        void toMermaid() override;
        void toLLVM() override;
        void analyze() override;
        Expression::Base* leftValue;
        Expression::Base* expression;
    };
}

#endif //SED_AST_NODE_ASSIGNMENT_STATEMENT_HPP
