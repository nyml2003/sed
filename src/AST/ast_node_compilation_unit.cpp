//
// Created by venty on 2024/3/17.
//

#include "ast_node_compilation_unit.hpp"
#include "../Context/llvm_assist_context.hpp"
#include "../Context/analyze_context.hpp"
namespace Compiler::AST {
    CompilationUnit::CompilationUnit(){
        nodeType = NODE_TYPE::COMPILATION_UNIT;
    }

    void CompilationUnit::toMermaid() {
        std::cout << id << "[CompilationUnit]" << std::endl;
        for (size_t it = 0; it < children.size(); it++) {
            std::cout << id << "--" << it << "-->" << children[it]->id << std::endl;
            children[it]->toMermaid();
        }
    }

    void CompilationUnit::toLLVM() {
        llvmAssistContext.enter();
        for (auto &child : children) {
            child->toLLVM();
        }
        llvmAssistContext.leave();
        llvmAssistContext.module->print(llvm::errs(), nullptr);
    }

    void CompilationUnit::analyze() {
        analyzeContext.enter();
        for (auto &child : children) {
            child->analyze();
        }
        analyzeContext.leave();
    }

    void CompilationUnit::attach(std::vector<Base *> t) {
        children = std::move(t);
        begin = children[0]->begin;
        end = children[children.size() - 1]->end;
    }
} // namespace Compiler::AST