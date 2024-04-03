#pragma once
#include "args_types.hpp"
#include <map>
#include <memory>
using namespace args_types;
namespace args_parse
{

    /// @brief Функция для обработки аргументов командной строки.
    /// 
    /// Просто берет и обрабатывает.
    /// 
    /// @attention
    /// Подразумевается, что все аргументы имеют корректное значение.
    ///
    void EatParams(
        /// Сколько всего аргументов.
        int argc,
        /// Значения аргументов. Должно быть ровно @a argc.
        const char** argv);
    /// @brief Функция для определения является ли строка числом
    /// Возвращает истину/ложь

    class ArgsParser
    {
    public:
        virtual void add(std::unique_ptr<Arg> ptr);
        virtual args_error::ParseResult parse(int argc, const char** argv);
        virtual std::unique_ptr<Arg> getArgumentFromVector(int index);
        void SetValidator(args_validator::ParserValidator* validator);
        ArgsParser();
        ~ArgsParser() {};
    private:
        virtual args_error::ParseResult tryParse(const std::string& parseable_arg);
        virtual std::string extractParameter(const std::string & source, std::string& extractable);
        virtual args_error::ParseResult setParamsInLongNameWithEqual(const std::string& source, std::unique_ptr<Arg>const& arg,const char**argv, int&index);
        virtual args_error::ParseResult setParamsInShortNameWithEqual(const std::string& source, std::unique_ptr<Arg>const& arg);
        virtual args_error::ParseResult setParamsInShortNameWithoutEqual(const std::string& source, std::unique_ptr<Arg>const& arg, const char** argv, int &index);
        virtual args_error::ParseResult parseLongNameArgument(const std::string& source, const char**argv, int &index);
        virtual args_error::ParseResult parseShortNameArgument(const std::string& source, const char**argv, int &index);
        args_validator::ParserValidator* _validator;
        std::vector<std::unique_ptr<Arg>> Args;
    protected:
        
    };
}/* namespace args_parse */

