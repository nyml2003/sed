//
// Created by venty on 2024/3/17.
//

#include "ast_expression_identifier.hpp"
#include "llvm_assist_context.hpp"
#include "analyze_context.hpp"

namespace Compiler::AST::Expression
{
    Identifier::Identifier(std::string name)
    {
        this->name = std::move(name);
    }

    void Identifier::toMermaid()
    {
        std::cout << "Identifier" << std::endl;
    }

    /**
     * @brief
     *
     * @details
     */
    void Identifier::toLLVM()
    {
        bool isGlobal = llvmAssistContext.isGlobal();
        llvm::Type* type =llvmAssistContext.types.back();
        llvmAssistContext.types.pop_back();
        if (isGlobal) {
            Context::Message<llvm::Value*> message = llvmAssistContext.get(name);
            if (message.success) {
                auto* global = llvm::cast<llvm::GlobalVariable>(message.value);
                llvm::Value* value = llvmAssistContext.builder->CreateLoad(global->getValueType(), global);
                llvmAssistContext.values.push_back(value);
            } else {
                auto* global = new llvm::GlobalVariable(*llvmAssistContext.module, type, false, llvm::GlobalValue::ExternalLinkage, nullptr, name);
                global->setAlignment(llvm::MaybeAlign(4));
                llvmAssistContext.set(name, global);
                llvmAssistContext.values.push_back(global);
            }
        } else {
            Context::Message<llvm::Value*> message = llvmAssistContext.get(name);
            if (message.success) {
                auto* local = llvm::cast<llvm::AllocaInst>(message.value);
                llvm::Value* value = llvmAssistContext.builder->CreateLoad(local->getAllocatedType(), local);
                llvmAssistContext.values.push_back(value);
            } else {
                llvm::AllocaInst* local = llvmAssistContext.builder->CreateAlloca(type, nullptr, name);
                llvmAssistContext.set(name, local);
                llvmAssistContext.values.push_back(local);
            }
        }
    }

    void Identifier::analyze()
    {
        analyzeContext.expressions.push_back(this);
    }

    EXPRESSION_TYPE Identifier::getType()
    {
        return getValue()->getType();
    }

    Base* Identifier::getValue()
    {
        Context::Message<Base*> message = analyzeContext.get(name);
        if (message.success) {
            return message.value;
        } else {
            printLocation("Undefined identifier: " + name);
            exit(1);
        }
    }
}