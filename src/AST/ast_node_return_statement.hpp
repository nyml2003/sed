//
// Created by DELL on 2024/3/18.
//

#ifndef SED_AST_NODE_RETURN_STATEMENT_HPP
#define SED_AST_NODE_RETURN_STATEMENT_HPP
#include "ast_node_base.hpp"
#include "Expression/ast_expression_base.hpp"
namespace Compiler::AST {
    struct ReturnStatement : public Base {
        void toMermaid() override;
        void toLLVM() override;
        void analyze() override;
        explicit ReturnStatement();
        explicit ReturnStatement(Expression::Base* expression);
        Expression::Base* expression;
    };
} // Compiler

#endif //SED_AST_NODE_RETURN_STATEMENT_HPP
