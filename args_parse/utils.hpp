#pragma once
#include <string>
#include "args_types.hpp"
namespace utils
{
        bool stringToBool(const std::string& str);
        std::string boolToString(const bool param);
        /**
        * @brief Метод, выделяющее короткое имя длинного аргумента
        */
        std::string extractShortFormOfLongName(
            // Передаваемый в метод аргумент
            const std::string& str
        );
        std::string enumToString(args_types::ArgumentsType type);
   
   
}/*namespace utils*/