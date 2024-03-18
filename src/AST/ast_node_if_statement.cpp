//
// Created by DELL on 2024/3/18.
//

#include "ast_node_if_statement.hpp"
#include "../Context/llvm_assist_context.hpp"

namespace Compiler::AST{
    IfStatement::IfStatement(Expression::Base* condition, Base* thenBlock, Base* elseBlock) {
        this->condition = condition;
        this->thenBlock = thenBlock;
        this->elseBlock = elseBlock;
        begin = condition->begin;
        end = elseBlock ? elseBlock->end : thenBlock->end;
        nodeType = NODE_TYPE::IF_STATEMENT;
    }

    IfStatement::IfStatement(Expression::Base* condition, Base* thenBlock) {
        this->condition = condition;
        this->thenBlock = thenBlock;
        this->elseBlock = nullptr;
        begin = condition->begin;
        end = thenBlock->end;
        nodeType = NODE_TYPE::IF_STATEMENT;
    }

    void IfStatement::toMermaid() {
        std::cout << id << "[IfStatement]" << std::endl;
        std::cout << id << "--condition-->" << condition->id << std::endl;
        condition->toMermaid();
        std::cout << id << "--thenBlock-->" << thenBlock->id << std::endl;
        thenBlock->toMermaid();
        if (elseBlock) {
            std::cout << id << "--elseBlock-->" << elseBlock->id << std::endl;
            elseBlock->toMermaid();
        }
    }

    void IfStatement::toLLVM() {
        //TODO
    }
}