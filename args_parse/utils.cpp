#include "utils.hpp"
#include <algorithm>
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
}