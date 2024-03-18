//
// Created by venty on 2024/3/17.
//

#include "ast_expression_binary_expression.hpp"
#include "ast_expression_boolean.hpp"
#include "ast_expression_int32.hpp"
#include "ast_expression_float32.hpp"
#include "Context/llvm_assist_context.hpp"
#include "Context/analyze_context.hpp"

namespace Compiler::AST::Expression {
    static Base *eval(Operator op, Base *left, Base *right) {
        EXPRESSION_TYPE leftType = left->getType();
        EXPRESSION_TYPE rightType = right->getType();
        switch (leftType) {
            case EXPRESSION_TYPE::BOOLEAN:
                switch (rightType) {
                    case EXPRESSION_TYPE::BOOLEAN:
                        switch (op) {
                            case Operator::AND:
                                return new Boolean(
                                        dynamic_cast<Boolean *>(left)->value && dynamic_cast<Boolean *>(right)->value);
                            case Operator::OR:
                                return new Boolean(
                                        dynamic_cast<Boolean *>(left)->value || dynamic_cast<Boolean *>(right)->value);
                            default:
                                std::cerr << "BinaryExpression::eval: Unknown operator" << std::endl;
                                exit(1);
                        }
                    default:
                        std::cerr << "BinaryExpression::eval: Unknown right type" << std::endl;
                        exit(1);
                }
            case EXPRESSION_TYPE::INT32:
                switch (rightType) {
                    case EXPRESSION_TYPE::INT32:
                        switch (op) {
                            case Operator::ADD:
                                return new Int32(
                                        dynamic_cast<Int32 *>(left)->value + dynamic_cast<Int32 *>(right)->value);
                            case Operator::SUB:
                                return new Int32(
                                        dynamic_cast<Int32 *>(left)->value - dynamic_cast<Int32 *>(right)->value);
                            case Operator::MUL:
                                return new Int32(
                                        dynamic_cast<Int32 *>(left)->value * dynamic_cast<Int32 *>(right)->value);
                            case Operator::DIV:
                                return new Int32(
                                        dynamic_cast<Int32 *>(left)->value / dynamic_cast<Int32 *>(right)->value);
                            case Operator::MOD:
                                return new Int32(
                                        dynamic_cast<Int32 *>(left)->value % dynamic_cast<Int32 *>(right)->value);
                            case Operator::EQ:
                                return new Boolean(
                                        dynamic_cast<Int32 *>(left)->value == dynamic_cast<Int32 *>(right)->value);
                            case Operator::NE:
                                return new Boolean(
                                        dynamic_cast<Int32 *>(left)->value != dynamic_cast<Int32 *>(right)->value);
                            case Operator::LT:
                                return new Boolean(
                                        dynamic_cast<Int32 *>(left)->value < dynamic_cast<Int32 *>(right)->value);
                            case Operator::GT:
                                return new Boolean(
                                        dynamic_cast<Int32 *>(left)->value > dynamic_cast<Int32 *>(right)->value);
                            case Operator::LE:
                                return new Boolean(
                                        dynamic_cast<Int32 *>(left)->value <= dynamic_cast<Int32 *>(right)->value);
                            case Operator::GE:
                                return new Boolean(
                                        dynamic_cast<Int32 *>(left)->value >= dynamic_cast<Int32 *>(right)->value);
                            default:
                                std::cerr << "BinaryExpression::eval: Unknown operator" << std::endl;
                                exit(1);
                        }
                    case EXPRESSION_TYPE::FLOAT32:
                        switch (op) {
                            case Operator::ADD:
                                return new Float32(
                                        (float)dynamic_cast<Int32 *>(left)->value + dynamic_cast<Float32 *>(right)->value);
                            case Operator::SUB:
                                return new Float32(
                                        (float)dynamic_cast<Int32 *>(left)->value - dynamic_cast<Float32 *>(right)->value);
                            case Operator::MUL:
                                return new Float32(
                                        (float)dynamic_cast<Int32 *>(left)->value * dynamic_cast<Float32 *>(right)->value);
                            case Operator::DIV:
                                return new Float32(
                                        (float)dynamic_cast<Int32 *>(left)->value / dynamic_cast<Float32 *>(right)->value);
                            case Operator::EQ:
                                return new Boolean(
                                        (float)dynamic_cast<Int32 *>(left)->value == dynamic_cast<Float32 *>(right)->value);
                            case Operator::NE:
                                return new Boolean(
                                        (float)dynamic_cast<Int32 *>(left)->value != dynamic_cast<Float32 *>(right)->value);
                            case Operator::LT:
                                return new Boolean(
                                        (float)dynamic_cast<Int32 *>(left)->value < dynamic_cast<Float32 *>(right)->value);
                            case Operator::GT:
                                return new Boolean(
                                        (float)dynamic_cast<Int32 *>(left)->value > dynamic_cast<Float32 *>(right)->value);
                            case Operator::LE:
                                return new Boolean(
                                        (float)dynamic_cast<Int32 *>(left)->value <= dynamic_cast<Float32 *>(right)->value);
                            case Operator::GE:
                                return new Boolean(
                                        (float)dynamic_cast<Int32 *>(left)->value >= dynamic_cast<Float32 *>(right)->value);
                            default:
                                std::cerr << "BinaryExpression::eval: Unknown operator" << std::endl;
                                exit(1);
                        }
                    default:
                        std::cerr << "BinaryExpression::eval: Unknown right type" << std::endl;
                        exit(1);
                }
            case EXPRESSION_TYPE::FLOAT32:
                switch (rightType) {
                    case EXPRESSION_TYPE::FLOAT32:
                        switch (op) {
                            case Operator::ADD:
                                return new Float32(
                                        dynamic_cast<Float32 *>(left)->value + dynamic_cast<Float32 *>(right)->value);
                            case Operator::SUB:
                                return new Float32(
                                        dynamic_cast<Float32 *>(left)->value - dynamic_cast<Float32 *>(right)->value);
                            case Operator::MUL:
                                return new Float32(
                                        dynamic_cast<Float32 *>(left)->value * dynamic_cast<Float32 *>(right)->value);
                            case Operator::DIV:
                                return new Float32(
                                        dynamic_cast<Float32 *>(left)->value / dynamic_cast<Float32 *>(right)->value);
                            case Operator::EQ:
                                return new Boolean(
                                        dynamic_cast<Float32 *>(left)->value == dynamic_cast<Float32 *>(right)->value);
                            case Operator::NE:
                                return new Boolean(
                                        dynamic_cast<Float32 *>(left)->value != dynamic_cast<Float32 *>(right)->value);
                            case Operator::LT:
                                return new Boolean(
                                        dynamic_cast<Float32 *>(left)->value < dynamic_cast<Float32 *>(right)->value);
                            case Operator::GT:
                                return new Boolean(
                                        dynamic_cast<Float32 *>(left)->value > dynamic_cast<Float32 *>(right)->value);
                            case Operator::LE:
                                return new Boolean(
                                        dynamic_cast<Float32 *>(left)->value <= dynamic_cast<Float32 *>(right)->value);
                            case Operator::GE:
                                return new Boolean(
                                        dynamic_cast<Float32 *>(left)->value >= dynamic_cast<Float32 *>(right)->value);
                            default:
                                std::cerr << "BinaryExpression::eval: Unknown operator" << std::endl;
                                exit(1);
                        }
                    case EXPRESSION_TYPE::INT32:
                        switch (op) {
                            case Operator::ADD:
                                return new Float32(
                                        dynamic_cast<Float32 *>(left)->value + (float)dynamic_cast<Int32 *>(right)->value);
                            case Operator::SUB:
                                return new Float32(
                                        dynamic_cast<Float32 *>(left)->value - (float)dynamic_cast<Int32 *>(right)->value);
                            case Operator::MUL:
                                return new Float32(
                                        dynamic_cast<Float32 *>(left)->value * (float)dynamic_cast<Int32 *>(right)->value);
                            case Operator::DIV:
                                return new Float32(
                                        dynamic_cast<Float32 *>(left)->value / (float)dynamic_cast<Int32 *>(right)->value);
                            case Operator::EQ:
                                return new Boolean(
                                        dynamic_cast<Float32 *>(left)->value == (float)dynamic_cast<Int32 *>(right)->value);
                            case Operator::NE:
                                return new Boolean(
                                        dynamic_cast<Float32 *>(left)->value != (float)dynamic_cast<Int32 *>(right)->value);
                            case Operator::LT:
                                return new Boolean(
                                        dynamic_cast<Float32 *>(left)->value < (float)dynamic_cast<Int32 *>(right)->value);
                            case Operator::GT:
                                return new Boolean(
                                        dynamic_cast<Float32 *>(left)->value > (float)dynamic_cast<Int32 *>(right)->value);
                            case Operator::LE:
                                return new Boolean(
                                        dynamic_cast<Float32 *>(left)->value <= (float)dynamic_cast<Int32 *>(right)->value);
                            case Operator::GE:
                                return new Boolean(
                                        dynamic_cast<Float32 *>(left)->value >= (float)dynamic_cast<Int32 *>(right)->value);
                            default:
                                std::cerr << "BinaryExpression::eval: Unknown operator" << std::endl;
                                exit(1);
                        }
                    default:
                        std::cerr << "BinaryExpression::eval: Unknown right type" << std::endl;
                        exit(1);
                }
            default:
                std::cerr << "BinaryExpression::eval: Unknown left type" << std::endl;
                exit(1);
        }
    }

    BinaryExpression::BinaryExpression(Operator op, Base *left, Base *right) : op(op), left(left), right(right) {}

    void BinaryExpression::toMermaid() {
        std::cout << id << "[" << "BinaryExpression: " << operatorName[static_cast<int>(op)] << "]" << std::endl;
        std::cout << id << " --> " << left->id << std::endl;
        left->toMermaid();
        std::cout << id << " --> " << right->id << std::endl;
        right->toMermaid();
    }

    void BinaryExpression::toLLVM() {
        left->toLLVM();
        right->toLLVM();
        auto rightValue = llvmAssistContext.values.back();
        llvmAssistContext.values.pop_back();
        auto leftValue = llvmAssistContext.values.back();
        llvmAssistContext.values.pop_back();
        switch (op) {
            case Operator::ADD:
                llvmAssistContext.values.push_back(llvmAssistContext.builder->CreateAdd(leftValue, rightValue));
                break;
            case Operator::SUB:
                llvmAssistContext.values.push_back(llvmAssistContext.builder->CreateSub(leftValue, rightValue));
                break;
            case Operator::MUL:
                llvmAssistContext.values.push_back(llvmAssistContext.builder->CreateMul(leftValue, rightValue));
                break;
            case Operator::DIV:
                llvmAssistContext.values.push_back(llvmAssistContext.builder->CreateSDiv(leftValue, rightValue));
                break;
            case Operator::MOD:
                llvmAssistContext.values.push_back(llvmAssistContext.builder->CreateSRem(leftValue, rightValue));
                break;
            case Operator::AND:
                llvmAssistContext.values.push_back(llvmAssistContext.builder->CreateAnd(leftValue, rightValue));
                break;
            case Operator::OR:
                llvmAssistContext.values.push_back(llvmAssistContext.builder->CreateOr(leftValue, rightValue));
                break;
            case Operator::EQ:
                llvmAssistContext.values.push_back(llvmAssistContext.builder->CreateICmpEQ(leftValue, rightValue));
                break;
            case Operator::NE:
                llvmAssistContext.values.push_back(llvmAssistContext.builder->CreateICmpNE(leftValue, rightValue));
                break;
            case Operator::LT:
                llvmAssistContext.values.push_back(llvmAssistContext.builder->CreateICmpSLT(leftValue, rightValue));
                break;
            case Operator::GT:
                llvmAssistContext.values.push_back(llvmAssistContext.builder->CreateICmpSGT(leftValue, rightValue));
                break;
            case Operator::LE:
                llvmAssistContext.values.push_back(llvmAssistContext.builder->CreateICmpSLE(leftValue, rightValue));
                break;
            case Operator::GE:
                llvmAssistContext.values.push_back(llvmAssistContext.builder->CreateICmpSGE(leftValue, rightValue));
                break;
            default:
                std::cerr << "BinaryExpression::toLLVM: Unknown operator" << std::endl;
                exit(1);
        }
    }

    void BinaryExpression::analyze() {
        left->analyze();
        right->analyze();
        Base *rightValue = analyzeContext.expressions.back();
        analyzeContext.expressions.pop_back();
        Base *leftValue = analyzeContext.expressions.back();
        analyzeContext.expressions.pop_back();
        analyzeContext.expressions.push_back(eval(op, leftValue, rightValue));
    }

    EXPRESSION_TYPE BinaryExpression::getType() {
        return getValue()->getType();
    }

    Base *BinaryExpression::getValue() {
        left = left->getValue();
        right = right->getValue();
        return eval(op, left, right);
    }

}

