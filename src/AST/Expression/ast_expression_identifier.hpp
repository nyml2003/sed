//
// Created by venty on 2024/3/17.
//

#ifndef SED_AST_EXPRESSION_IDENTIFIER_HPP
#define SED_AST_EXPRESSION_IDENTIFIER_HPP
#include "ast_expression_base.hpp"
namespace Compiler::AST::Expression {
    struct Identifier : public Base {
        explicit Identifier(std::string name);
        void toMermaid() override;
        void toLLVM() override;
        void analyze() override;
        EXPRESSION_TYPE getType() override;
        Base* getValue() override;
        std::string name;
    };
}

#endif //SED_AST_EXPRESSION_IDENTIFIER_HPP
