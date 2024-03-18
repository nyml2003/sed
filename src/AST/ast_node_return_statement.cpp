//
// Created by DELL on 2024/3/18.
//

#include "ast_node_return_statement.hpp"
#include "ast_node_function_definition.hpp"
#include "../Context/analyze_context.hpp"

namespace Compiler::AST{
    ReturnStatement::ReturnStatement() {
        nodeType = NODE_TYPE::RETURN_STATEMENT;
    }

    ReturnStatement::ReturnStatement(Expression::Base* expression) {
        this->expression = expression;
        begin = expression->begin;
        end = expression->end;
        nodeType = NODE_TYPE::RETURN_STATEMENT;
    }

    void ReturnStatement::toMermaid() {
        std::cout << id << "[ReturnStatement]" << std::endl;
        if (expression) {
            std::cout << id << "--expression-->" << expression->id << std::endl;
            expression->toMermaid();
        }
    }

    void ReturnStatement::toLLVM() {
        //TODO
    }

    void ReturnStatement::analyze() {
        expression = expression->getValue();
    }
}
