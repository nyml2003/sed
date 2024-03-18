//
// Created by venty on 2024/3/17.
//

#ifndef SED_AST_EXPRESSION_FLOAT32_HPP
#define SED_AST_EXPRESSION_FLOAT32_HPP
#include "ast_expression_base.hpp"
namespace Compiler::AST::Expression {
    struct Float32 : public Base {
        explicit Float32(float value);
        void toMermaid() override;
        void toLLVM() override;
        void analyze() override;
        EXPRESSION_TYPE getType() override;
        Base* getValue() override;
        float value;
    };
}

#endif //SED_AST_EXPRESSION_FLOAT32_HPP
