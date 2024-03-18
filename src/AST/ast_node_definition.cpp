//
// Created by venty on 2024/3/17.
//

#include "ast_node_definition.hpp"
#include "../Context/llvm_assist_context.hpp"
#include "ast_node_inner_type.hpp"
#include "Context/analyze_context.hpp"

namespace Compiler::AST{
    Definition::Definition(Base* leftValue, Base* initializerValue) : leftValue(leftValue), initialValue(initializerValue) {
        begin = leftValue->begin;
        end = initializerValue->end;
        nodeType = NODE_TYPE::DEFINITION;
    }

    void Definition::toMermaid() {
        std::cout << id << "[Definition]" << std::endl;
        std::cout << id << "--leftValue-->" << leftValue->id << std::endl;
        leftValue->toMermaid();
        std::cout << id << "--initialValue-->" << initialValue->id << std::endl;
        initialValue->toMermaid();
    }

    /**
     * @brief
     *
     * @details
     *
     * @param
     *
     * @return
     */
    void Definition::toLLVM() {
        leftValue->toLLVM();
        initialValue->toLLVM();
        if (llvmAssistContext.isGlobal()){
            llvm::Value* value = llvmAssistContext.values.back();
            llvmAssistContext.values.pop_back();
            auto* global = llvm::cast<llvm::GlobalVariable>(llvmAssistContext.values.back());
            llvmAssistContext.values.pop_back();
            if (llvm::isa<llvm::Constant>(value)){
                global->setInitializer(llvm::cast<llvm::Constant>(value));
            } else {
                llvmAssistContext.builder->CreateStore(value, global);
            }
        }else{
            auto* local = llvm::cast<llvm::AllocaInst>(llvmAssistContext.values.back());
            llvmAssistContext.values.pop_back();
            llvm::Value* value = llvmAssistContext.values.back();
            llvmAssistContext.values.pop_back();
            llvmAssistContext.builder->CreateStore(value, local);
        }
    }

    /**
     * @brief 检查左值和右值的类型是否一致
     */
    void Definition::analyze() {
        leftValue->analyze();
        initialValue->analyze();
        InnerType leftType = analyzeContext.types.back();
        analyzeContext.types.pop_back();
        InnerType rightType = analyzeContext.types.back();
        analyzeContext.types.pop_back();
        if (leftType != rightType){
            printLocation("Type mismatch");
            exit(1);
        }
    }
}