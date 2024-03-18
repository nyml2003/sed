//
// Created by venty on 2024/3/18.
//

#include "ast_node_function_definition.hpp"

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
        block->toLLVM();
    }

    void FunctionDefinition::analyze() {
        returnType->analyze();
        block->analyze();
    }
} // Compiler::AST