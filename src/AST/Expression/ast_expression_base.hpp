//
// Created by 风唤长河 on 2024/3/17.
//

#ifndef SED_AST_EXPRESSION_BASE_HPP
#define SED_AST_EXPRESSION_BASE_HPP

#include "../ast_node_base.hpp"

namespace Compiler::AST::Expression {
    enum class EXPRESSION_TYPE {
        INT32,
        FLOAT32,
        BOOLEAN,
        UNKNOWN,
    };

    struct Base : public Compiler::AST::Base {
        explicit Base();

        ~Base() override = default;

        void toMermaid() override = 0;

        void toLLVM() override = 0;

        void analyze() override = 0;

        /**
         * @brief 返回表达式的类型
         * @return
         */
        virtual EXPRESSION_TYPE getType() = 0;

        /**
         * @brief 返回表达式的值
         * @return
         */
        virtual Base *getValue() = 0;
    };
}

#endif // SED_AST_EXPRESSION_BASE_HPP
