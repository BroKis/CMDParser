#pragma once
#include "args_types.hpp"
#include <map>
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

    bool isInteger(const std::string& s);
    void check_next(int argc, int& index, const char** argv, string& temp);
    bool isBoolean(const std::string& s);

    class ArgsParser
    {
    public:
        virtual void add(Arg*arg);
        virtual bool parse(int argc, const char** argv);
      
        ArgsParser();
        ~ArgsParser();
    private:
        virtual void setArguments(string temp_arg, Arg* arg);
        virtual bool tryParse(int index,string parseable_arg);
        vector<Arg*> Args;
    protected:
        
    };
}/* namespace args_parse */

