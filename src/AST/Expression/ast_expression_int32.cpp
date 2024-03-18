//
// Created by venty on 2024/3/17.
//

#include "ast_expression_int32.hpp"
#include "Context/analyze_context.hpp"
#include "Context/llvm_assist_context.hpp"

namespace Compiler::AST::Expression{
    Int32::Int32(int32_t value) : value(value) {}

    void Int32::toMermaid() {
        std::cout << id << "[" << "Int32: " << value << "]" << std::endl;
    }

    void Int32::toLLVM() {
        llvmAssistContext.values.push_back(llvm::ConstantInt::get(llvm::Type::getInt32Ty(*llvmAssistContext.context), value));
    }

    void Int32::analyze() {
        analyzeContext.expressions.push_back(this);
    }

    EXPRESSION_TYPE Int32::getType() {
        return EXPRESSION_TYPE::INT32;
    }

    Base *Int32::getValue() {
        return this;
    }
}