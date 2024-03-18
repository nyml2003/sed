//
// Created by venty on 2024/3/18.
//

#ifndef SED_AST_EXPRESSION_LEFT_VALUE_HPP
#define SED_AST_EXPRESSION_LEFT_VALUE_HPP

#include <vector>
#include "ast_expression_base.hpp"

namespace Compiler::AST::Expression {
    struct LeftValue : public Base {
        explicit LeftValue(Base* identifier, std::vector<Base*> index);
        explicit LeftValue(Base* leftValue);
        void toMermaid() override;
        void toLLVM() override;
        void analyze() override;
        EXPRESSION_TYPE getType() override;
        Base* getValue() override;

        Base* identifier;
        std::vector<Base*> index;
    };
}

#endif //SED_AST_EXPRESSION_LEFT_VALUE_HPP
