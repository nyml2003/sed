//
// Created by venty on 2024/3/18.
//

#include "ast_expression_initial_value.hpp"
#include "ast_expression_base.hpp"
#include "analyze_context.hpp"

namespace Compiler::AST::Expression {
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
        if (children.size() == 1) {
            children[0]->analyze();
            analyzeContext.types.push_back(children[0]->getType());
        } else {
            std::cerr << "Array not implemented" << std::endl;
            exit(1);
        }
    }

    EXPRESSION_TYPE InitialValue::getType() {
        return getValue()->getType();
    }

    Base *InitialValue::getValue() {
        if (children.size() == 1) {
            return children[0]->getValue();
        } else {
            std::cerr << "Array not implemented" << std::endl;
            exit(1);
        }
    }
}