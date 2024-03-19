//
// Created by DELL on 2024/3/19.
//

#ifndef SED_AST_EXPRESSION_UNDEFINED_HPP
#define SED_AST_EXPRESSION_UNDEFINED_HPP
#include "ast_expression_base.hpp"
namespace Compiler::AST::Expression {
    struct Undefined : public Base {
        explicit Undefined();
        ~Undefined() override = default;
        void toMermaid() override;
        void toLLVM() override;
        void analyze() override;
        EXPRESSION_TYPE getType() override;
        Base *getValue() override;
    };
}

#endif //SED_AST_EXPRESSION_UNDEFINED_HPP
