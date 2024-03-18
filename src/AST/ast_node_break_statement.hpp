//
// Created by DELL on 2024/3/18.
//

#ifndef SED_AST_NODE_BREAK_STATEMENT_HPP
#define SED_AST_NODE_BREAK_STATEMENT_HPP
#include "ast_node_base.hpp"
namespace Compiler::AST{
    struct BreakStatement : public Base {
        explicit BreakStatement();
        void toMermaid() override;
        void toLLVM() override;
        void analyze() override;
    };
}



#endif //SED_AST_NODE_BREAK_STATEMENT_HPP
