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

    class ArgsParser
    {
    public:
        virtual void add(Arg*arg);
        virtual bool parse(int argc, const char** argv);
    protected:
        vector<Arg*> Args;
    };
}/* namespace args_parse */

