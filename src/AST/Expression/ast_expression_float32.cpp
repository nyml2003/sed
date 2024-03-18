//
// Created by venty on 2024/3/17.
//

#include "ast_expression_float32.hpp"
#include "../Context/llvm_assist_context.hpp"
#include "../Context/analyze_context.hpp"

namespace Compiler::AST::Expression {
    Float32::Float32(float value) : value(value) {}

    void Float32::toMermaid() {
        std::cout << id << "[" << "Float32: " << value << "]" << std::endl;
    }

    void Float32::toLLVM() {
        llvmAssistContext.values.push_back(llvm::ConstantFP::get(llvm::Type::getFloatTy(*llvmAssistContext.context), value));
    }

    void Float32::analyze() {
        analyzeContext.expressions.push_back(this);
    }

    EXPRESSION_TYPE Float32::getType() {
        return EXPRESSION_TYPE::FLOAT32;
    }

    Base *Float32::getValue() {
        return this;
    }
}