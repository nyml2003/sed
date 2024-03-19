//
// Created by venty on 2024/3/17.
//

#include "ast_node_definition.hpp"
#include "llvm_assist_context.hpp"
#include "ast_node_inner_type.hpp"
#include "analyze_context.hpp"
#include "ast_expression_identifier.hpp"
#include "ast_expression_undefined.hpp"
#include "ast_expression_int32.hpp"
#include "ast_expression_float32.hpp"
#include "ast_expression_left_value.hpp"

namespace Compiler::AST{
    Definition::Definition(Expression::Base *leftValue, Expression::Base *initializerValue) {
        begin = leftValue->begin;
        end = initializerValue->end;
        nodeType = NODE_TYPE::DEFINITION;
    }

    Definition::Definition(Expression::Base *leftValue) {
        this->leftValue = leftValue;
        this->initialValue = new Expression::Undefined();
        begin = leftValue->begin;
        end = leftValue->end;
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
     * @details 先调用左值的toLLVM方法，将左值存入values中，然后调用右值的toLLVM方法，将右值存入values中
     *
     * @param
     *
     * @return
     */
    void Definition::toLLVM() {
        leftValue->toLLVM();
        llvm::Value* leftValue = llvmAssistContext.values.back();
        llvmAssistContext.values.pop_back();
        initialValue->toLLVM();
        llvm::Value* initialValue = llvmAssistContext.values.back();
        llvmAssistContext.values.pop_back();
        //如果右值是一个未定义的值，那么就不需要创建store指令
        if (initialValue->getType()->isVoidTy()){
            return;
        }
        llvmAssistContext.builder->CreateStore(initialValue, leftValue);
    }

    /**
     * @brief 检查左值和右值的类型是否一致
     */
    void Definition::analyze() {
        initialValue = initialValue->getValue();
        leftValue = leftValue->getValue();

        if (initialValue->getType() == Expression::EXPRESSION_TYPE::UNDEFINED){
            Expression::EXPRESSION_TYPE type = analyzeContext.types.back();
            switch (type){
                case Expression::EXPRESSION_TYPE::INT32:
                    initialValue = new Expression::Int32(0);
                    break;
                case Expression::EXPRESSION_TYPE::FLOAT32:
                    initialValue = new Expression::Float32(0);
                    break;
                default:
                    std::cerr << "Definition::analyze: Unknown type" << std::endl;
                    exit(1);
            }
        }

        if (leftValue->getType() != initialValue->getType()){
            printLocation("Type mismatch");
            exit(1);
        }

        Expression::Identifier* identifier = dynamic_cast<Expression::LeftValue*>(leftValue)->identifier;
        auto message = analyzeContext.add(identifier->name, initialValue);

    }
}