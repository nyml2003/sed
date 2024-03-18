//
// Created by venty on 2024/3/17.
//

#include "ast_expression_unary_expression.hpp"
#include "ast_expression_int32.hpp"
#include "ast_expression_float32.hpp"
#include "ast_expression_boolean.hpp"
#include "Context/llvm_assist_context.hpp"
#include "Context/analyze_context.hpp"

namespace Compiler::AST::Expression
{
    static Base* eval(Operator op, Base* value)
    {
        switch (op)
        {
            case Operator::MINUS:
                if (value->getType() == EXPRESSION_TYPE::INT32)
                {
                    return new Int32(-dynamic_cast<Int32*>(value)->value);
                }
                else if (value->getType() == EXPRESSION_TYPE::FLOAT32)
                {
                    return new Float32(-dynamic_cast<Float32*>(value)->value);
                }
                else
                {
                    std::cerr << "UnaryExpression::eval: Invalid type for operator -" << std::endl;
                    exit(1);
                }
            case Operator::NOT:
                if (value->getType() == EXPRESSION_TYPE::BOOLEAN)
                {
                    return new Boolean(!dynamic_cast<Boolean*>(value)->value);
                }
                else
                {
                    std::cerr << "UnaryExpression::eval: Invalid type for operator !" << std::endl;
                    exit(1);
                }
            default:
                std::cerr << "UnaryExpression::eval: Unknown operator" << std::endl;
                exit(1);
        }
    }
    UnaryExpression::UnaryExpression(Operator op, Base* value)
    {
        this->op = op;
        this->expression = value;
    }

    void UnaryExpression::toMermaid()
    {
        std::cout << id << "[" << operatorName[static_cast<int>(op)] << "]" << std::endl;
        std::cout << id << " --> " << expression->id << std::endl;
        expression->toMermaid();
    }

    void UnaryExpression::toLLVM()
    {
        expression->toLLVM();
        llvm::Value* value = llvmAssistContext.values.back();
        llvmAssistContext.values.pop_back();
        switch (op)
        {
            case Operator::MINUS:
                llvmAssistContext.values.push_back(llvmAssistContext.builder->CreateNeg(value));
                break;
            case Operator::NOT:
                llvmAssistContext.values.push_back(llvmAssistContext.builder->CreateNot(value));
                break;
            default:
                std::cerr << "UnaryExpression::toLLVM: Unknown operator" << std::endl;
                exit(1);
        }
    }

    void UnaryExpression::analyze()
    {
        expression->analyze();
        Base* value = analyzeContext.expressions.back();
        analyzeContext.expressions.pop_back();
        analyzeContext.expressions.push_back(eval(op, value));
    }

    EXPRESSION_TYPE UnaryExpression::getType()
    {
        return getValue()->getType();
    }

    Base* UnaryExpression::getValue()
    {
        expression = expression->getValue();
        return eval(op, expression);
    }
}