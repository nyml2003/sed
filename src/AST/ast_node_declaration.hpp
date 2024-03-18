//
// Created by venty on 2024/3/17.
//

#ifndef SED_AST_NODE_DECLARATION_HPP
#define SED_AST_NODE_DECLARATION_HPP
#include "ast_node_base.hpp"
#include "ast_node_definition.hpp"
#include "ast_node_decorator.hpp"
#include "ast_node_inner_type.hpp"
namespace Compiler::AST {
    struct Declaration : public Base {
        explicit Declaration(InnerType type, std::vector<Base*> definitions);
        void toMermaid() override;
        void toLLVM() override;
        void analyze() override;
        void addDecorator(Decorator decorator);
        InnerType type;
        std::vector<Base*> definitions;
        std::vector<Decorator> decorators;
    };
}
#endif //SED_AST_NODE_DECLARATION_HPP
