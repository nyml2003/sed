//
// Created by venty on 2024/3/17.
//

#include "ast_expression_identifier.hpp"
#include "llvm_assist_context.hpp"
#include "analyze_context.hpp"
#include "ast_expression_undefined.hpp"

namespace Compiler::AST::Expression {
    Identifier::Identifier(std::string name) {
        this->name = std::move(name);
    }

    void Identifier::toMermaid() {
        std::cout << id << "[" << "Identifier: " << name << "]" << std::endl;
    }

    /**
     * @brief
     *
     * @details identifier是一个表达式，它的toLLVM方法会将它的值存入values中
     */
    void Identifier::toLLVM() {
        llvm::Type *type = llvmAssistContext.types.back();
        llvmAssistContext.types.pop_back();
        Context::Message<llvm::Value *> message = llvmAssistContext.get(name);
        if (message.success) {
            llvmAssistContext.values.push_back(
                    llvmAssistContext.builder->CreateLoad(type, message.value)
            );
        } else {
            llvm::Value* value;
            if (llvmAssistContext.isGlobal()) {
                value = new llvm::GlobalVariable(*llvmAssistContext.module, type, false,
                                                       llvm::GlobalValue::ExternalLinkage, nullptr, name);
            } else {
                value = llvmAssistContext.builder->CreateAlloca(type, nullptr, name);
            }
            message = llvmAssistContext.add(name, value);
            if (!message.success) {
                printLocation(message.message);
                exit(1);
            }
            llvmAssistContext.values.push_back(value);
        }
    }

    void Identifier::analyze() {
        analyzeContext.expressions.push_back(this);
    }

    EXPRESSION_TYPE Identifier::getType() {
        return getValue()->getType();
    }

    Base *Identifier::getValue() {
        Context::Message<Base *> message = analyzeContext.get(name);
        if (message.success) {
            return message.value;
        } else {
            printLocation("Undefined identifier: " + name);
            exit(1);
        }
    }
}