//
// Created by DELL on 2024/3/18.
//

#include "ast_node_while_statement.hpp"

namespace Compiler::AST{
    WhileStatement::WhileStatement(Expression::Base* condition, Base* block) {
        this->condition = condition;
        this->block = block;
        begin = condition->begin;
        end = block->end;
        nodeType = NODE_TYPE::WHILE_STATEMENT;
    }

    void WhileStatement::toMermaid() {
        std::cout << id << "[WhileStatement]" << std::endl;
        std::cout << id << "--condition-->" << condition->id << std::endl;
        condition->toMermaid();
        std::cout << id << "--block-->" << block->id << std::endl;
        block->toMermaid();
    }

    void WhileStatement::toLLVM() {
        //TODO
    }

    void WhileStatement::analyze() {
        condition->analyze();
        block->analyze();
    }
}