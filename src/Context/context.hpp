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
        std::vector< std::map<std::string, Value> > variables;
        /**
         * @brief 插入一个变量，如果变量已经存在则返回错误
         */
        Message<Value> add(std::string name, Value value);
        /**
         * @brief 获取一个变量，如果变量不存在则返回错误
         */
        Message<Value> get(std::string name);
        /**
         * @brief 确认一个变量是否存在
         */
        Message<Value> has(std::string name);
        /**
         * @brief 给一个变量赋值，如果变量不存在则返回错误
         */
        Message<Value> set(std::string name, Value value);
        /**
         * @brief 进入一个新的作用域
         */
        void enter();
        /**
         * @brief 离开一个作用域
         */
        void leave();
        /**
         * @brief 判断当前是否在全局作用域,如果在全局作用域则返回true，否则返回false
         * @details 如果只有一个作用域则返回true，否则返回false
         */
        bool isGlobal();
    };
}
#endif //SED_CONTEXT_HPP
