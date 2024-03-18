//
// Created by venty on 2024/3/18.
//

#include "ast_expression_left_value.hpp"
#include "Expression/ast_expression_base.hpp"

namespace Compiler::AST::Expression {
    LeftValue::LeftValue(Base* leftValue, std::vector<Base*> index) {
        identifier = leftValue;
        this->index = index;
        begin = leftValue->begin;
        end = index.back()->end;
        nodeType = NODE_TYPE::LEFT_VALUE;
    }

    LeftValue::LeftValue(Base* leftValue) {
        identifier = leftValue;
        begin = leftValue->begin;
        end = leftValue->end;
        nodeType = NODE_TYPE::LEFT_VALUE;
    }

    void LeftValue::toMermaid() {
        std::cout << id << "[LeftValue]" << std::endl;
        std::cout << id << "--identifier-->" << identifier->id << std::endl;
        identifier->toMermaid();
        for (size_t it = 0; it < index.size(); it++) {
            std::cout << id << "--index" << it << "-->" << index[it]->id << std::endl;
            index[it]->toMermaid();
        }
    }

    /**
     * @TODO 还没有实现数组的处理
     */
    void LeftValue::toLLVM() {
        identifier->toLLVM();
    }

    /**
     * @brief index应该都是整数
     */
    void LeftValue::analyze() {
        identifier->analyze();
        for (auto &it : index) {
            it->analyze();
            if (it->getType() != Compiler::AST::Expression::EXPRESSION_TYPE::INT32) {
                std::cout << "Index should be integer" << std::endl;
            }
        }
    }

    EXPRESSION_TYPE LeftValue::getType() {
        return identifier->getType();
    }

    Base* LeftValue::getValue() {
        return identifier->getValue();
    }
}