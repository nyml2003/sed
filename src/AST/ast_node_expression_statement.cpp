//
// Created by DELL on 2024/3/18.
//

#include "ast_node_expression_statement.hpp"

namespace Compiler::AST {
    ExpressionStatement::ExpressionStatement(Expression::Base* expression) {
        this->expression = expression;
        begin = expression->begin;
        end = expression->end;
        nodeType = NODE_TYPE::EXPRESSION_STATEMENT;
    }

    void ExpressionStatement::toMermaid() {
        std::cout << id << "[ExpressionStatement]" << std::endl;
        std::cout << id << "--expression-->" << expression->id << std::endl;
        expression->toMermaid();
    }

    void ExpressionStatement::toLLVM() {
        expression->toLLVM();
    }

    void ExpressionStatement::analyze() {
        expression->analyze();
    }
}