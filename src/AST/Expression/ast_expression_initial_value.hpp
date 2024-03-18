//
// Created by venty on 2024/3/18.
//

#ifndef SED_AST_EXPRESSION_INITIAL_VALUE_HPP
#define SED_AST_EXPRESSION_INITIAL_VALUE_HPP

#include "ast_expression_base.hpp"
#include <vector>
namespace Compiler::AST::Expression {
    struct InitialValue : public Base {
        explicit InitialValue(Base *child);
        explicit InitialValue(std::vector<Base *> children);
        void toMermaid() override;
        void toLLVM() override;
        void analyze() override;
        EXPRESSION_TYPE getType() override;
        Base* getValue() override;
        std::vector<Base *> children;
    };
}

#endif //SED_AST_EXPRESSION_INITIAL_VALUE_HPP
