//
// Created by venty on 2024/3/17.
//

#ifndef SED_AST_NODE_COMPILATION_UNIT_HPP
#define SED_AST_NODE_COMPILATION_UNIT_HPP
#include "ast_node_base.hpp"
#include <vector>
namespace Compiler::AST {
    struct CompilationUnit : public Base {
        explicit CompilationUnit();
        void toMermaid() override;
        void toLLVM() override;
        void analyze() override;
        void attach(std::vector<Base*> children);
        std::vector<Base*> children;
    };
}

#endif //SED_AST_NODE_COMPILATION_UNIT_HPP
