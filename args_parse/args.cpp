#include "args.hpp"

#include <iostream>

namespace args_parse
{

	void EatParams(int argc, const char** argv)
	{
		for (int i = 0; i < argc; ++i)
		{
			std::cout << "[" << i << "]: '" << argv[i] << "'" << std::endl;
		}
	}

	void removeCharsFromString(string& str, char* charsToRemove) {
		for (unsigned int i = 0; i < strlen(charsToRemove); ++i) {
			str.erase(remove(str.begin(), str.end(), charsToRemove[i]), str.end());
		}
	}

	void check_next(int argc,int& index, const char** argv, string& temp)
	{
		string next_arg = argv[index + 1];
		if (strncmp("-", next_arg.c_str(), 1) != 0 && index + 1 < argc)
		{
			temp = temp + next_arg;
			index++;
		}
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
			if (strncmp("--", temp_arg.c_str(), 2) == 0)
			{

				for (const auto& arg : Args)
				{
					if (temp_arg.find(arg->getLongName()) != string::npos)
					{
						check_next(argc, i, argv, temp_arg);
						if (temp_arg.find('=') != string::npos)
						{
							string erased = "--" + arg->getLongName() + "=";
							temp_arg.erase(0, erased.size());

						}
						else if (temp_arg.find('=') == string::npos)
						{
							string erased = "--" + arg->getLongName();
							temp_arg.erase(0, erased.size());
						}
					}
				}
			}
			else if (strncmp("-", temp_arg.c_str(), 1) == 0)
			{
				for (const auto& arg : Args)
				{
					if (temp_arg[1] == arg->getShortName())
					{
						check_next(argc, i, argv, temp_arg);
						if (temp_arg.find('=') != string::npos)
						{
							temp_arg.erase(0, 3);
							
						}
						else if (temp_arg.find('=') == string::npos)
						{
							temp_arg.erase(0, 2);
						}
					}
				}
			}
			
		}
		return true;
	}



} /* namespace args_parse */

