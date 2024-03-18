//
// Created by venty on 2024/3/18.
//

#include "context.hpp"

namespace Compiler::Context {
    template<typename Value>
    Message<Value> Context<Value>::add(std::string name, Value value) {
        if (variables.back().find(name) != variables.back().end()) {
            return {false, "Variable already exists", Value()};
        }
        variables.back()[name] = value;
        return {true, "Success", value};
    }

    template<typename Value>
    Message<Value> Context<Value>::get(std::string name) {
        for (auto it = variables.rbegin(); it != variables.rend(); it++) {
            if (it->find(name) != it->end()) {
                return {true, "Success", it->at(name)};
            }
        }
        return {false, "Variable not found", Value()};
    }

    template<typename Value>
    Message<Value> Context<Value>::has(std::string name) {
        for (auto it = variables.rbegin(); it != variables.rend(); it++) {
            if (it->find(name) != it->end()) {
                return {true, "Success", Value()};
            }
        }
        return {false, "Variable not found", Value()};
    }

    template<typename Value>
    Message<Value> Context<Value>::set(std::string name, Value value) {
        for (auto it = variables.rbegin(); it != variables.rend(); it++) {
            if (it->find(name) != it->end()) {
                it->at(name) = value;
                return {true, "Success", value};
            }
        }
        return {false, "Variable not found", Value()};
    }

    template<typename Value>
    void Context<Value>::enter() {
        variables.push_back(std::map<std::string, Value>());
    }

    template<typename Value>
    void Context<Value>::leave() {
        variables.pop_back();
    }

    template<typename Value>
    bool Context<Value>::isGlobal() {
        return variables.size() == 1;
    }
}