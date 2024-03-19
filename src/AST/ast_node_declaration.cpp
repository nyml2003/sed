//
// Created by venty on 2024/3/17.
//

#include "ast_node_declaration.hpp"
#include "analyze_context.hpp"
#include "llvm_assist_context.hpp"

namespace Compiler::AST{
    Declaration::Declaration(InnerType type, std::vector<Base*> definitions) : type(type), definitions(std::move(definitions)) {
        nodeType = NODE_TYPE::DECLARATION;
        idCounter++; // 为type分配id
    }

    void Declaration::toMermaid() {
        std::cout << id << "[Declaration:";
        for (auto decorator : decorators) {
            std::cout << decoratorName[static_cast<int>(decorator)] << " ";
        }
        std::cout << "]" << std::endl;
        std::cout << id << "--type-->" << id+1 << innerType[static_cast<int>(type)] << std::endl;
        for (size_t it = 0; it < definitions.size(); it++) {
            std::cout << id << "--definition" << it << "-->" << definitions[it]->id << std::endl;
            definitions[it]->toMermaid();
        }
    }

    void Declaration::toLLVM() {
        switch(type){
            case InnerType::INT:
                llvmAssistContext.types.push_back(llvm::Type::getInt32Ty(*llvmAssistContext.context));
                break;
            case InnerType::FLOAT:
                llvmAssistContext.types.push_back(llvm::Type::getFloatTy(*llvmAssistContext.context));
                break;
            default:
                printLocation("Unknown type");
                exit(1);
        }
        for (auto definition : definitions) {
            definition->toLLVM();
        }
    }

    void Declaration::analyze() {
        bool hasConst = false;
        for (auto decorator : decorators) {
            if (decorator == Decorator::CONSTANT) {
                hasConst = true;
                break;
            }
        }
        switch(type){
            case InnerType::INT:
                analyzeContext.types.push_back(Expression::EXPRESSION_TYPE::INT32);
                break;
            case InnerType::FLOAT:
                analyzeContext.types.push_back(Expression::EXPRESSION_TYPE::FLOAT32);
                break;
            default:
                printLocation("Unknown type");
                exit(1);
        }

        for (auto definition : definitions) {
             if (hasConst) {
                 /**
                  * 在语法分析阶段, 没有区分常量和变量, 所以在这里进行检查
                  */
                 if (definition->nodeType == NODE_TYPE::LEFT_VALUE) {
                    printLocation("Constant declaration must be initialized");
                    exit(1);
                }
             }
            definition->analyze();
        }
        analyzeContext.types.pop_back();
    }

    void Declaration::addDecorator(Decorator decorator) {
        decorators.push_back(decorator);
    }
}