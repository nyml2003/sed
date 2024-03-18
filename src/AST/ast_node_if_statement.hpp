//
// Created by DELL on 2024/3/18.
//

#ifndef SED_AST_NODE_IF_STATEMENT_HPP
#define SED_AST_NODE_IF_STATEMENT_HPP
#include "ast_node_base.hpp"
#include "Expression/ast_expression_base.hpp"

namespace Compiler::AST {
    struct IfStatement : public Base {
        explicit IfStatement(Expression::Base* condition, Base* thenBlock, Base* elseBlock);
        explicit IfStatement(Expression::Base* condition, Base* thenBlock);
        void toMermaid() override;
        void toLLVM() override;
        void analyze() override;
        Expression::Base* condition;
        Base* thenBlock;
        Base* elseBlock;
    };
}

#endif //SED_AST_NODE_IF_STATEMENT_HPP
