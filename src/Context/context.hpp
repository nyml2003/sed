//
// Created by venty on 2024/3/18.
//

#ifndef SED_CONTEXT_HPP
#define SED_CONTEXT_HPP
#include <map>
#include <vector>
#include <string>
#include "message.hpp"
namespace Compiler::Context {
    template<typename Value>
    struct Context {
        Context() = default;
        ~Context() = default;

        std::vector< std::map<std::string, Value> > variables;
        /**
         * @brief 插入一个变量，如果变量已经存在则返回错误
         */
        Message<Value> add(std::string name, Value value){
            if (variables.back().find(name) != variables.back().end()) {
                return {false, "Variable already exists", Value()};
            }
            variables.back()[name] = value;
            return {true, "Success", value};
        }
        /**
         * @brief 获取一个变量，如果变量不存在则返回错误
         */
        Message<Value> get(std::string name){
            for (auto it = variables.rbegin(); it != variables.rend(); it++) {
                if (it->find(name) != it->end()) {
                    return {true, "Success", it->at(name)};
                }
            }
            return {false, "Variable not found", Value()};
        }
        /**
         * @brief 确认一个变量是否存在
         */
        Message<Value> has(std::string name){
            for (auto it = variables.rbegin(); it != variables.rend(); it++) {
                if (it->find(name) != it->end()) {
                    return {true, "Success", Value()};
                }
            }
            return {false, "Variable not found", Value()};
        }
        /**
         * @brief 给一个变量赋值，如果变量不存在则返回错误
         */
        Message<Value> set(std::string name, Value value){
            for (auto it = variables.rbegin(); it != variables.rend(); it++) {
                if (it->find(name) != it->end()) {
                    it->at(name) = value;
                    return {true, "Success", value};
                }
            }
            return {false, "Variable not found", Value()};
        }
        /**
         * @brief 进入一个新的作用域
         */
        void enter(){
            variables.push_back(std::map<std::string, Value>());
        }
        /**
         * @brief 离开一个作用域
         */
        void leave(){
            variables.pop_back();
        }
        /**
         * @brief 判断当前是否在全局作用域,如果在全局作用域则返回true，否则返回false
         * @details 如果只有一个作用域则返回true，否则返回false
         */
        bool isGlobal(){
            return variables.size() == 1;
        }
    };
}
#endif //SED_CONTEXT_HPP
