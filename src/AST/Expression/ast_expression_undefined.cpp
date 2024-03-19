//
// Created by DELL on 2024/3/19.
//

#include "ast_expression_undefined.hpp"
#include "llvm_assist_context.hpp"

namespace Compiler::AST::Expression {
    Undefined::Undefined() {
    }

    void Undefined::toMermaid() {
        std::cout << id << "[Undefined]" << std::endl;
    }

    void Undefined::toLLVM() {
        std::cerr << "Undefined value is not allowed to be used" << std::endl;
        exit(1);
    }

    void Undefined::analyze() {

    }

    EXPRESSION_TYPE Undefined::getType() {
        return EXPRESSION_TYPE::UNDEFINED;
    }

    Base *Undefined::getValue() {
        return this;
    }
}