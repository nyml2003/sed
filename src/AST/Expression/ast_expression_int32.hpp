//
// Created by venty on 2024/3/17.
//

#ifndef SED_AST_EXPRESSION_INT32_HPP
#define SED_AST_EXPRESSION_INT32_HPP

#include "ast_expression_base.hpp"

namespace Compiler::AST::Expression {
    struct Int32 : public Base {
        explicit Int32(int32_t value);
        void toMermaid() override;
        void toLLVM() override;
        void analyze() override;
        EXPRESSION_TYPE getType() override;
        Base* getValue() override;
        int32_t value;
    };

}

#endif //SED_AST_EXPRESSION_INT32_HPP
