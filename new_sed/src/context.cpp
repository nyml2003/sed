//
// Created by venty on 2024/3/24.
//
#include "context.hpp"
#include "error.hpp"
#include <iostream>

namespace SED::Context
{

    AnalyzerContext::AnalyzerContext()
    {
        variables.push_back(std::map<std::string, AST::DirectRightValue *>());
        functions.push_back(std::map<std::string, AST::ValueType>());
    }

    void AnalyzerContext::add(AST::Variable *variable, AST::DirectRightValue *value)
    {
        std::string name = variable->getName();
        if (variables.back().find(name) != variables.back().end())
        {
            Error::VariableRedeclarationError(name).error();
        }
        variables.back()[name] = value;
    }

    AST::DirectRightValue *AnalyzerContext::get(AST::Variable *variable)
    {
        std::string name = variable->getName();
        for (auto it = variables.rbegin(); it != variables.rend(); it++)
        {
            if (it->find(name) != it->end())
            {
                return it->at(name);
            }
        }
        Error::UndefinedVariableError(name).error();
        return nullptr;
    }

    bool AnalyzerContext::exists(AST::Variable *variable)
    {

        std::string name = variable->getName();
        for (auto it = variables.rbegin(); it != variables.rend(); it++)
        {
            if (it->find(name) != it->end())
            {
                return true;
            }
        }
        return false;
    }
    void AnalyzerContext::set(AST::Variable *variable, AST::DirectRightValue *value)
    {
        std::string name = variable->getName();
        for (auto it = variables.rbegin(); it != variables.rend(); it++)
        {
            if (it->find(name) != it->end())
            {
                it->at(name) = value;
                return;
            }
        }
        Error::UndefinedVariableError(name).error();
    }


    void AnalyzerContext::add(std::string name, AST::ValueType type)
    {
        if (functions.back().find(name) != functions.back().end())
        {
            Error::FunctionRedeclarationError(name).error();
        }
        functions.back()[name] = type;
    }

    bool AnalyzerContext::exists(std::string name)
    {
        for (auto it = functions.rbegin(); it != functions.rend(); it++)
        {
            if (it->find(name) != it->end())
            {
                return true;
            }
        }
        return false;
    }

    AST::ValueType AnalyzerContext::get(std::string name)
    {
        for (auto it = functions.rbegin(); it != functions.rend(); it++)
        {
            if (it->find(name) != it->end())
            {
                return it->at(name);
            }
        }
        Error::UndefinedFunctionError(name).error();
        return AST::ValueType::VOID;
    }
}