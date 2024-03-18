//
// Created by venty on 2024/3/18.
//

#include "ast_node_initial_value.hpp"
#include "AST/Expression/ast_expression_base.hpp"

namespace Compiler::AST {
    InitialValue::InitialValue(Base *child) : children({child}) {
        begin = child->begin;
        end = child->end;
        nodeType = NODE_TYPE::INITIAL_VALUE;
    }

    InitialValue::InitialValue(std::vector<Base *> children) : children(std::move(children)) {
        begin = this->children.front()->begin;
        end = this->children.back()->end;
        nodeType = NODE_TYPE::INITIAL_VALUE;
    }

    void InitialValue::toMermaid() {
        std::cout << id << "[InitialValue]" << std::endl;
        for (size_t it = 0; it < children.size(); it++) {
            std::cout << id << "--child" << it << "-->" << children[it]->id << std::endl;
            children[it]->toMermaid();
        }
    }

    /**
     * @TODO 还没有实现数组的处理
     */
    void InitialValue::toLLVM() {
        if (children.size() == 1) {
            children[0]->toLLVM();
        } else {
            std::cerr << "Array not implemented" << std::endl;
            exit(1);
        }
    }

    void InitialValue::analyze() {
        for (size_t it = 0; it < children.size(); it++) {
            if (dynamic_cast<AST::Expression::Base *>(children[it]) != nullptr) {
                children[it] = dynamic_cast<AST::Expression::Base *>(children[it])->getValue();
            } else if (dynamic_cast<AST::InitialValue *>(children[it]) != nullptr) {
                dynamic_cast<AST::InitialValue *>(children[it])->analyze();
            } else {
                std::cerr << "InitialValue::analyze: unknown type" << std::endl;
                exit(1);
            }
        }
    }
} // Compiler::AST