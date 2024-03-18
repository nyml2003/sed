//
// Created by DELL on 2024/3/18.
//

#ifndef SED_AST_NODE_CONTINUE_STATEMENT_HPP
#define SED_AST_NODE_CONTINUE_STATEMENT_HPP
#include "ast_node_base.hpp"
namespace Compiler::AST{
    struct ContinueStatement : public Base {
        void toMermaid() override;
        void toLLVM() override;
        void analyze() override;
        explicit ContinueStatement();
    };
}

#endif //SED_AST_NODE_CONTINUE_STATEMENT_HPP
