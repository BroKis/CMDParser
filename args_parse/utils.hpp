#pragma once
#include <string>
#include "args_types.hpp"
namespace utils
{
    class Utils
    {
    public:
        static bool stringToBool(const std::string& str);
        static std::string boolToString(const bool param);
        static std::string extractShortFormOfLongName(const std::string& str);
        static std::string enumToString(args_types::ArgumentsType type);
    };
   
}