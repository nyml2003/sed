
#ifndef SED_ERROR_DUMP_HPP
#define SED_ERROR_DUMP_HPP
#include "enumeration.hpp"
#include <map>
#include <string>
#include <vector>
namespace SED::AST
{
class Constant;
class Variable;

} // namespace SED::AST

namespace SED::Error
{

extern std::map<Enumeration::ValueType, std::string> errorValueTypeMap;
extern std::string errorValueTypeWrapper(Enumeration::ValueType valueType);
extern std::map<Enumeration::Operator, std::string> errorOperatorMap;
extern std::string errorOperatorWrapper(Enumeration::Operator op);

class Error
{
  protected:
    enum class Type
    {
        ERROR,
        WARNING,
        INFO,
        DEBUG
    } type;
    enum class Code
    {
        SYNTAX_ERROR,
        SEMANTIC_ERROR,
        RUNTIME_ERROR
    } code;
    explicit Error(Type type, Code code, std::string message);
    std::string message;
    static std::map<Code, std::string> CodeEnumMap;
    static std::map<Type, std::string> TypeEnumMap;
    static std::string CodeEnumMapToString(Code code);
    static std::string TypeEnumMapToString(Type type);

  public:
    void info();
    void warning();
    void error();
    void debug();
};

class TypeMismatchError : public Error
{
  public:
    explicit TypeMismatchError(Enumeration::ValueType type1, Enumeration::ValueType type2);
};

class UndeclaredVariableError : public Error
{
  public:
    explicit UndeclaredVariableError(std::string variable);
};

class UndeclaredFunctionError : public Error
{
  public:
    explicit UndeclaredFunctionError(std::string function);
};

class InvalidOperationError : public Error
{
  public:
    explicit InvalidOperationError(Enumeration::ValueType type1, Enumeration::Operator op,
                                   Enumeration::ValueType type2);
    explicit InvalidOperationError(Enumeration::ValueType type1, Enumeration::Operator op);
};

class VariableRedeclarationError : public Error
{
  public:
    explicit VariableRedeclarationError(std::string variable);
};

class FunctionRedeclarationError : public Error
{
  public:
    explicit FunctionRedeclarationError(std::string function);
};

class DivisionByZeroError : public Error
{
  public:
    explicit DivisionByZeroError();
};

// 条件语句中的条件表达式不是bool类型
class ConditionNotBoolError : public Error
{
  public:
    explicit ConditionNotBoolError(Enumeration::ValueType type);
};

} // namespace SED::Error

#endif // !SED_ERROR_DUMP_HPP