//
// Created by DELL on 2024/3/18.
//

#include "ast_node_continue_statement.hpp"

namespace Compiler::AST{
    ContinueStatement::ContinueStatement() {
        nodeType = NODE_TYPE::CONTINUE_STATEMENT;
    }

    void ContinueStatement::toMermaid() {
        std::cout << id << "[ContinueStatement]" << std::endl;
    }

    void ContinueStatement::toLLVM() {
        //TODO
    }

    void ContinueStatement::analyze() {
        //TODO
    }
}