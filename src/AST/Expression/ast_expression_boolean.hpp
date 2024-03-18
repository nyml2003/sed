//
// Created by venty on 2024/3/17.
//

#ifndef SED_AST_EXPRESSION_BOOLEAN_HPP
#define SED_AST_EXPRESSION_BOOLEAN_HPP
#include "ast_expression_base.hpp"
namespace Compiler::AST::Expression {
    struct Boolean : public Base {
        explicit Boolean(bool value);
        void toMermaid() override;
        void toLLVM() override;
        void analyze() override;
        EXPRESSION_TYPE getType() override;
        Base* getValue() override;
        bool value;
    };
}

#endif //SED_AST_EXPRESSION_BOOLEAN_HPP
