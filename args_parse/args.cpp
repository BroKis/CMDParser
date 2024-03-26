#include "args.hpp"

#include <iostream>

namespace args_parse
{

void EatParams(int argc, const char ** argv)
{
    for(int i = 0; i < argc; ++i)
    {
        std::cout << "[" << i << "]: '" << argv[i] << "'" << std::endl;
    }
}

void removeCharsFromString(string& str, char* charsToRemove) {
    for (unsigned int i = 0; i < strlen(charsToRemove); ++i) {
        str.erase(remove(str.begin(), str.end(), charsToRemove[i]), str.end());
    }
}

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

void ArgsParser::add(Arg* arg)
{
    Args.push_back(arg);
}
bool ArgsParser::parse(int argc, const char** argv)
{
    for (int i = 1; i < argc; i++)
    {
        string temp_arg = argv[i];
        for (const auto& arg : Args)
        {
            if(strncmp("-", temp_arg.c_str(), 1)==0)
            {
                if (temp_arg.find(arg->getShortName()) == string::npos)
                {

                }

            }
            else if (strncmp("-",temp_arg.c_str(), 2)==0)
            {

            }
            
           
        }
    }
    return true;
}



} /* namespace args_parse */

