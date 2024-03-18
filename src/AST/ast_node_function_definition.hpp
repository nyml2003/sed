//
// Created by venty on 2024/3/18.
//

#ifndef SED_AST_NODE_FUNCTION_DEFINITION_HPP
#define SED_AST_NODE_FUNCTION_DEFINITION_HPP
#include "ast_node_base.hpp"
#include "ast_node_inner_type.hpp"

namespace Compiler::AST{
    struct FunctionDefinition : public Base {
        explicit FunctionDefinition(InnerType returnType, Base* identifier, Base* block);
        void toMermaid() override;
        void toLLVM() override;
        void analyze() override;
        InnerType returnType;
        Base* identifier;
        Base* block;
    };
}


#endif //SED_AST_NODE_FUNCTION_DEFINITION_HPP
