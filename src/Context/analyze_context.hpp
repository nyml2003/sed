//
// Created by venty on 2024/3/18.
//

#ifndef SED_ANALYZE_CONTEXT_HPP
#define SED_ANALYZE_CONTEXT_HPP
#include "../AST/Expression/ast_expression_base.hpp"
#include "../AST/ast_node_inner_type.hpp"
#include "context.hpp"
#include "ast_node_function_definition.hpp"

namespace Compiler::Context {
    struct AnalyzeContext :public Context<Compiler::AST::Expression::Base*> {
        AnalyzeContext();
        ~AnalyzeContext();
        std::vector<Compiler::AST::Expression::Base*> expressions;
        std::vector< Compiler::AST::InnerType > types;
        std::vector< Compiler::AST::FunctionDefinition* > functions;
    };
}
inline Compiler::Context::AnalyzeContext analyzeContext = Compiler::Context::AnalyzeContext();
#endif //SED_ANALYZE_CONTEXT_HPP
