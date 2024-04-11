#include "utils.hpp"
#include <algorithm>
#include <regex>
namespace utils
{
	bool stringToBool(const std::string& str)
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

    std::string boolToString(const bool param)
    {
        return param ? "true" : "false";
    }
   
    std::string extractShortFormOfLongName(const std::string& str)
    {
        static std::regex pattern("--([^=]+)=|--([^=]+)");
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

    std::chrono::microseconds chronoToMicroseconds(long long value, std::string &unit)
    {
        std::chrono::microseconds ms;
        if (unit == "d") {
            auto seconds = std::chrono::seconds(value);
            ms = std::chrono::microseconds(seconds);
        }
        else if (unit == "h") {
            auto seconds = std::chrono::seconds(value);
            ms = std::chrono::microseconds(seconds);
        }
        else if (unit == "m") {
            auto seconds = std::chrono::seconds(value);
            ms = std::chrono::microseconds(seconds);
        }
        else if (unit == "s") {
            auto seconds = std::chrono::seconds(value);
            ms = std::chrono::microseconds(seconds);
        }
        else if (unit == "ms") {
            auto milliseconds = std::chrono::milliseconds(value);
            ms = std::chrono::microseconds(milliseconds);
        }
        else if (unit == "us") {
            ms = std::chrono::microseconds(value);
        }
        else if (unit == "ns") {
            auto nanoseconds = std::chrono::milliseconds(value);
            ms = std::chrono::microseconds(nanoseconds);
        }
        return ms;
    }
}
   
    
