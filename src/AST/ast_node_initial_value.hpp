//
// Created by venty on 2024/3/18.
//

#ifndef SED_AST_NODE_INITIAL_VALUE_HPP
#define SED_AST_NODE_INITIAL_VALUE_HPP

#include "ast_node_base.hpp"
#include <vector>
namespace Compiler::AST {
    struct InitialValue : public Base {
        explicit InitialValue(Base *child);
        explicit InitialValue(std::vector<Base *> children);
        void toMermaid() override;
        void toLLVM() override;
        void analyze() override;
        std::vector<Base *> children;
    };
} // Compiler::AST

#endif //SED_AST_NODE_INITIAL_VALUE_HPP
