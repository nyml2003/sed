//
// Created by venty on 2024/3/18.
//

#include "llvm_assist_context.hpp"
namespace Compiler::Context {
    LLVMAssistContext::LLVMAssistContext() {
        context = new llvm::LLVMContext();
        module = new llvm::Module("main", *context);
        builder = new llvm::IRBuilder<>(*context);
    }

    LLVMAssistContext::~LLVMAssistContext() {

    }
} // Compiler