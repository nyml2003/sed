//
// Created by venty on 2024/3/18.
//

#ifndef SED_MESSAGE_HPP
#define SED_MESSAGE_HPP
#include <string>
namespace Compiler::Context{
    template<typename T>
    struct Message {
        bool success;
        std::string message;
        T value;
    };
}

#endif //SED_MESSAGE_HPP
