//
// Created by venty on 2024/3/18.
//

#ifndef SED_LLVM_ASSIST_CONTEXT_HPP
#define SED_LLVM_ASSIST_CONTEXT_HPP
#include "context.hpp"
#include <llvm/IR/Value.h>
#include <llvm/IR/IRBuilder.h>

namespace Compiler::Context {
    struct LLVMAssistContext : public Context<llvm::Value*> {
        LLVMAssistContext();
        ~LLVMAssistContext();
        llvm::Module* module;
        llvm::IRBuilder<>* builder;
        llvm::LLVMContext* context;
        std::vector<llvm::Function*> functions;
        std::vector<llvm::BasicBlock*> blocks;
        std::vector<llvm::Value*> values;
        std::vector<llvm::Type*> types;
    };
}
inline Compiler::Context::LLVMAssistContext llvmAssistContext = Compiler::Context::LLVMAssistContext();
#endif //SED_LLVM_ASSIST_CONTEXT_HPP
