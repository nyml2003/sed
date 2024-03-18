//
// Created by DELL on 2024/3/18.
//

#include "ast_node_break_statement.hpp"

namespace Compiler::AST{
    BreakStatement::BreakStatement() {
        nodeType = NODE_TYPE::BREAK_STATEMENT;
    }

    void BreakStatement::toMermaid() {
        std::cout << id << "[BreakStatement]" << std::endl;
    }

    void BreakStatement::toLLVM() {
        //TODO
    }
}