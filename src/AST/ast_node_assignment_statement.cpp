//
// Created by DELL on 2024/3/18.
//

#include "ast_node_assignment_statement.hpp"
#include "llvm_assist_context.hpp"

namespace Compiler::AST{
    AssignmentStatement::AssignmentStatement(Expression::Base* leftValue, Expression::Base* expression) {
        this->leftValue = leftValue;
        this->expression = expression;
        begin = leftValue->begin;
        end = expression->end;
        nodeType = NODE_TYPE::ASSIGN_STATEMENT;
    }

    void AssignmentStatement::toMermaid() {
        std::cout << id << "[AssignmentStatement]" << std::endl;
        std::cout << id << "--leftValue-->" << leftValue->id << std::endl;
        leftValue->toMermaid();
        std::cout << id << "--expression-->" << expression->id << std::endl;
        expression->toMermaid();
    }

    void AssignmentStatement::toLLVM() {
        leftValue->toLLVM();
        expression->toLLVM();
        llvm::Value* value = llvmAssistContext.values.back();
        llvmAssistContext.values.pop_back();
        llvm::Value* left = llvmAssistContext.values.back();
        llvmAssistContext.values.pop_back();
        llvmAssistContext.builder->CreateStore(value, left);
    }

    void AssignmentStatement::analyze() {
        expression = expression->getValue();
        if (leftValue->getType() != expression->getType()) {
            std::cout << "Type not match" << std::endl;
        }
        leftValue->analyze();
    }
}
