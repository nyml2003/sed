//
// Created by venty on 2024/3/17.
//

#ifndef SED_AST_NODE_BASE_HPP
#define SED_AST_NODE_BASE_HPP
#include "location.hh"
namespace Compiler::AST {
    enum class NODE_TYPE
    {
        COMPILATION_UNIT,
        DECLARATION,
        TYPE,
        DEFINITION,
        LEFT_VALUE,
        INITIAL_VALUE,
        FUNCTION_DEFINITION,
        BLOCK,
        ASSIGN_STATEMENT,
        EXPRESSION_STATEMENT,
        IF_STATEMENT,
        WHILE_STATEMENT,
        BREAK_STATEMENT,
        CONTINUE_STATEMENT,
        RETURN_STATEMENT,
        EXPRESSION,
        BASE,
    };
    struct Base {
        explicit Base();
        virtual ~Base() = default;
        virtual void toMermaid() = 0;
        virtual void toLLVM() = 0;
        virtual void analyze() = 0;
        void printLocation(const std::string& message) const;
        size_t id;
        static size_t idCounter;
        yy::position begin;
        yy::position end;
        NODE_TYPE nodeType;
    };
} // AST

#endif //SED_AST_NODE_BASE_HPP
