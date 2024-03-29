#include "args.hpp"
#include <iostream>
#include <algorithm>
namespace args_parse
{
	
	ArgsParser::ArgsParser() {};
	ArgsParser::~ArgsParser() {
		Args.clear();
	}
	const string degree = "=";

	void EatParams(int argc, const char** argv)
	{
		for (int i = 0; i < argc; ++i)
		{
			std::cout << "[" << i << "]: '" << argv[i] << "'" << std::endl;
		}
	}



	bool isInteger(const std::string& s) {
		if (s.empty())
			return false;

		
		size_t i = 0;
		if (s[i] == '+' || s[i] == '-')
			++i;

		for (; i < s.length(); ++i) {
			if (!std::isdigit(s[i]))
				return false;
		}

		return true;
	}


	bool ArgsParser::tryParse(int index,string parseable_arg)
	{
		string result;
		if (parseable_arg == "--")
		{
			result += "It is impossible to parse the string.It is assumed that there is a short command:";
			cout << result + parseable_arg << endl;
			return false;
		}
		else if (parseable_arg == "-")
		{
			result += "Argument parsing error.It is assumed that there is a long command:";
			cout << result + parseable_arg << endl;
			return false;
		}
		else if (isInteger(parseable_arg))
		{
			result += "Argument parsing error.A single input of a numeric argument is assumed:";
			cout << result + "["<<index<<"]"<<parseable_arg << endl;
			return false;
		}
		return true;
		
	}

	

	bool isBoolean(const std::string& s) {
		std::string lowercaseStr;
		for (char c : s) {
			lowercaseStr += std::tolower(c);
		}

		return lowercaseStr == "true" || lowercaseStr == "false";
	}
	void ArgsParser::setArguments(string temp_arg, Arg* arg)
	{

		if (isInteger(temp_arg)) {
			arg->addIntArg(stoi(temp_arg));

		}
		else if (isBoolean(temp_arg))
		{
			bool flag = temp_arg == "true" ? true : false;
			arg->addBoolArg(flag);
		}
		else
		{
			arg->addStringArg(temp_arg);
		}
	}
	void ArgsParser::add(Arg* arg)
	{
		Args.push_back(arg);
	}
	string boolToString(bool value) {
		return value ? "true" : "false";
	}
	
	
	
	bool ArgsParser::parse(int argc, const char** argv)
	{
		for (int i = 1; i < argc; i++)
		{
			string temp_arg = argv[i];
			if (tryParse(i,temp_arg))
			{
				if (temp_arg.find("--") != string::npos)
				{
					for (const auto& arg : Args)
					{
						if (temp_arg.find(arg->getLongName()) != string::npos)
						{
							
							if (temp_arg.find('=') != string::npos)
							{
							
								auto it = std::search(temp_arg.begin(), temp_arg.end(),
									degree.begin(), degree.end());
								string argument(it+1, temp_arg.end());
								setArguments(argument, arg);
								
							}
							else
							{
								setArguments(argv[++i], arg);
							}
						
							if (arg->isDefined() == false) { arg->setDefinded(true); }
							break;
						}
					}
				}
				else if (temp_arg.find("-") != string::npos)
				{
						for (const auto& arg : Args)
						{
							if (temp_arg.find(arg->getShortName()) != string::npos)
							{
								size_t pos = temp_arg.find(degree);
								char leftChar = (pos > 0) ? temp_arg[pos - 1] : '\0';
								if (temp_arg.find('=') != string::npos && leftChar == arg->getShortName())
								{
									
									auto it = std::search(temp_arg.begin(), temp_arg.end(),
										degree.begin(), degree.end());
									string argument(it+1, temp_arg.end());
									setArguments(argument, arg);
									
								}
								else
								{
									
									if (temp_arg.size() > 0)
									{
										setArguments(temp_arg, arg);
									}
									else
									{
										setArguments(argv[++i], arg);
									}
								}

								if (arg->isDefined() == false) { arg->setDefinded(true); }
								break;
							}
						}
				}
				else
				{
					string result = "Argument parsing error.It is assumed to enter a command or a single input of a string argument:";
					cout << result + "[" << i << "]" << temp_arg << endl;
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		return true;
	}
}/* namespace args_parse */

