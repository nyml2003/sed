//
// Created by venty on 2024/3/18.
//

#ifndef SED_AST_NODE_LEFT_VALUE_HPP
#define SED_AST_NODE_LEFT_VALUE_HPP

#include <vector>
#include "ast_node_base.hpp"
#include "AST/Expression/ast_expression_base.hpp"

namespace Compiler::AST {
    struct LeftValue : public Base {
        explicit LeftValue(Base* leftValue, std::vector<Compiler::AST::Expression::Base*> index);
        explicit LeftValue(Base* leftValue);
        void toMermaid() override;
        void toLLVM() override;
        void analyze() override;
        Base* identifier;
        std::vector<Compiler::AST::Expression::Base*> index;
    };
}

#endif //SED_AST_NODE_LEFT_VALUE_HPP
