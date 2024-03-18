//
// Created by venty on 2024/3/18.
//

#ifndef SED_AST_NODE_BLOCK_HPP
#define SED_AST_NODE_BLOCK_HPP
#include "ast_node_base.hpp"
#include <vector>
namespace Compiler::AST{
    struct Block : public Base {
        explicit Block();
        explicit Block(std::vector<Base*> statements);
        void toMermaid() override;
        void toLLVM() override;
        void analyze() override;
        std::vector<Base*> statements;
    };
}

#endif //SED_AST_NODE_BLOCK_HPP
