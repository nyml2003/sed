//
// Created by venty on 2024/3/18.
//

#include <llvm/IR/BasicBlock.h>
#include "ast_node_block.hpp"
#include "../Context/llvm_assist_context.hpp"
#include "../Context/analyze_context.hpp"

namespace Compiler::AST{
    Block::Block() {
        nodeType = NODE_TYPE::BLOCK;
    }

    Block::Block(std::vector<Base*> statements) : statements(std::move(statements)) {
        nodeType = NODE_TYPE::BLOCK;
        begin = this->statements.front()->begin;
        end = this->statements.back()->end;
    }

    void Block::toMermaid() {
        std::cout << id << "[Block]" << std::endl;
        for (size_t it = 0; it < statements.size(); it++) {
            std::cout << id << "--statement" << it << "-->" << statements[it]->id << std::endl;
            statements[it]->toMermaid();
        }
    }

    void Block::toLLVM() {
        llvm::BasicBlock *block = llvm::BasicBlock::Create(*llvmAssistContext.context, "entry", llvmAssistContext.functions.back());
        llvmAssistContext.builder->SetInsertPoint(block);
        llvmAssistContext.blocks.push_back(block);
        llvmAssistContext.enter();
        for (auto &statement : statements) {
            statement->toLLVM();
        }
        llvmAssistContext.leave();
        llvmAssistContext.blocks.pop_back();
    }

    void Block::analyze() {
        analyzeContext.enter();
        for (auto &statement : statements) {
            statement->analyze();
        }
        analyzeContext.leave();
    }
}