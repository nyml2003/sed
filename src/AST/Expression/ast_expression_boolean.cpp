//
// Created by venty on 2024/3/17.
//

#include "ast_expression_boolean.hpp"

namespace Compiler::AST::Expression
{
    Boolean::Boolean(bool value) : value(value) {}

    void Boolean::toMermaid()
    {
        std::cout << id << "[" << "Boolean: " << value << "]" << std::endl;
    }

    void Boolean::toLLVM()
    {
        llvmAssistContext.valueStack.push_back(llvm::ConstantInt::get(llvm::Type::getInt1Ty(llvmAssistContext.context), value));
    }

    void Boolean::analyze()
    {
        analyzeContext.expressionStack.push(this);
    }

    EXPRESSION_TYPE Boolean::getType()
    {
        return EXPRESSION_TYPE::BOOLEAN;
    }

    Base* Boolean::getValue()
    {
        return this;
    }
}