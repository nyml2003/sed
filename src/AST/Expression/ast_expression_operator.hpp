//
// Created by venty on 2024/3/17.
//

#ifndef SED_AST_EXPRESSION_OPERATOR_HPP
#define SED_AST_EXPRESSION_OPERATOR_HPP
#include <vector>
#include <string>
namespace Compiler::AST::Expression {
    enum class Operator {
        ADD,
        SUB,
        MUL,
        DIV,
        MOD,
        AND,
        OR,
        EQ,
        NE,
        LT,
        GT,
        LE,
        GE,
        NOT,
        PLUS,
        MINUS,
    };
    inline std::vector <std::string> operatorName = {
            "\"+\"",
            "\"-\"",
            "\"*\"",
            "\"/\"",
            "\"%\"",
            "\"&&\"",
            "\"||\"",
            "\"==\"",
            "\"!=\"",
            "\"<\"",
            "\">\"",
            "\"<=\"",
            "\">=\"",
            "\"!\"",
            "\"+\"",
            "\"-\"",
    };
}
#endif //SED_AST_EXPRESSION_OPERATOR_HPP
