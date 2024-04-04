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
        // ���� �������� �� �������� ������ ��� ���������� ��������� true/false, ���������� false
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
}