#include "utils.hpp"
#include <algorithm>
#include <regex>
namespace utils
{
	bool Utils::stringToBool(const std::string& str)
	{
        std::string lowercaseStr = str;
        std::transform(lowercaseStr.begin(), lowercaseStr.end(), lowercaseStr.begin(), ::tolower);

        if (lowercaseStr == "true" || lowercaseStr == "1") {
            return true;
        }
        else if (lowercaseStr == "false" || lowercaseStr == "0") {
            return false;
        }
        // Если значение не является числом или допустимым значением true/false, возвращает false
        return false;
	}

    std::string Utils::boolToString(const bool param)
    {
        return param ? "true" : "false";
    }

    std::string Utils::extractShortFormOfLongName(const std::string& str)
    {
        std::regex pattern("--([^=]+)=|--([^=]+)");
        std::smatch match;
        if (std::regex_search(str, match, pattern)) {
            if (match[1].length() > 0) {
                return match[1].str();
            }
            else if (match[2].length() > 0) {
                return match[2].str();
            }
        }
        return "";
    }
    std::string Utils::enumToString(args_types::ArgumentsType type)
    {
        switch (type)
        {
        case args_types::ArgumentsType::Int:  return "Int";
        case args_types::ArgumentsType::Bool:   return "Bool";
        case args_types::ArgumentsType::String: return "String";
        case args_types::ArgumentsType::Empty: return "Empty";
        default: return "[Unknown Argument Type]";
        }
    }
}