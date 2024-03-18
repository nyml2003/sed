//
// Created by venty on 2024/3/18.
//

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Verifier.h>
#include "ast_node_function_definition.hpp"
#include "Expression/ast_expression_identifier.hpp"
#include "../Context/llvm_assist_context.hpp"

namespace Compiler::AST {
    FunctionDefinition::FunctionDefinition(InnerType returnType, Base *identifier, Base *block) : returnType(returnType), identifier(identifier), block(block) {
        idCounter++; // 为returnType分配id
        begin = identifier->begin;
        end = block->end;
        end.line += 1;
        end.column = 0;
        nodeType = NODE_TYPE::FUNCTION_DEFINITION;
    }

    void FunctionDefinition::toMermaid() {
        std::cout << id << "[FunctionDefinition]" << std::endl;
        std::cout << id << "--returnType-->" << id + 1 << "[" << innerType[static_cast<int>(returnType)] << "]" << std::endl;
        std::cout << id << "--identifier-->" << identifier->id << std::endl;
        identifier->toMermaid();
        std::cout << id << "--block-->" << block->id << std::endl;
        block->toMermaid();
    }

    void FunctionDefinition::toLLVM() {
        llvm::FunctionType* functionType;
        switch (returnType) {
            case InnerType::INT:
                functionType = llvm::FunctionType::get(llvm::Type::getInt32Ty(*llvmAssistContext.context), false);
                break;
            case InnerType::VOID:
                functionType = llvm::FunctionType::get(llvm::Type::getVoidTy(*llvmAssistContext.context), false);
                break;
            case InnerType::FLOAT:
                functionType = llvm::FunctionType::get(llvm::Type::getFloatTy(*llvmAssistContext.context), false);
                break;
            default:
                std::cerr << "FunctionDefinition::toLLVM: returnType not supported" << std::endl;
                exit(1);
        }
        identifier->toLLVM();
        llvm::Function* function = llvm::Function::Create(
                functionType,
                llvm::Function::ExternalLinkage,
                dynamic_cast<Compiler::AST::Expression::Identifier*>(identifier)->name,
                llvmAssistContext.module
        );
        llvmAssistContext.functions.push_back(function);
        block->toLLVM();
        if (llvm::verifyFunction(*function, &llvm::errs())) {
            std::cerr << "FunctionDefinition::toLLVM: function verification failed" << std::endl;
            exit(1);
        }
        llvmAssistContext.functions.pop_back();
    }

    void FunctionDefinition::analyze() {
        block->analyze();
    }
} // Compiler::AST