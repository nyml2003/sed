//
// Created by DELL on 2024/3/18.
//

#ifndef SED_AST_NODE_WHILE_STATEMENT_HPP
#define SED_AST_NODE_WHILE_STATEMENT_HPP
#include "ast_node_base.hpp"
#include "Expression/ast_expression_base.hpp"

namespace Compiler::AST {
    struct WhileStatement : public Base {
        explicit WhileStatement(Expression::Base* condition, Base* block);
        void toMermaid() override;
        void toLLVM() override;
        void analyze() override;
        Expression::Base* condition;
        Base* block;
    };
}

#endif //SED_AST_NODE_WHILE_STATEMENT_HPP
