#include "args.hpp"

#include <iostream>

namespace args_parse
{
	
	ArgsParser::ArgsParser() {};
	ArgsParser::~ArgsParser() {
		Args.clear();
	}


	void EatParams(int argc, const char** argv)
	{
		for (int i = 0; i < argc; ++i)
		{
			std::cout << "[" << i << "]: '" << argv[i] << "'" << std::endl;
		}
	}



	bool isInteger(const std::string& s) {
		// Проверка на пустую строку
		if (s.empty())
			return false;

		// Проверка на знак числа
		size_t i = 0;
		if (s[i] == '+' || s[i] == '-')
			++i;

		// Проверка на наличие только цифр
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

	void check_next(int argc, int& index, const char** argv, string& temp)
	{
		if (index + 1 < argc)
		{
			string next_arg = argv[index + 1];
			if (strncmp("-", next_arg.c_str(), 1) != 0)
			{
				temp = temp + next_arg;
				index++;
			}
		}

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
								setArguments(temp_arg, arg);
								
							}
							else if (temp_arg.find('=') == string::npos)
							{
								string erased = "--" + arg->getLongName();
								temp_arg.erase(0, erased.size());
								setArguments(temp_arg, arg);
							}
							if (arg->isDefined() == false) { arg->setDefinded(true); }
							break;
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
									setArguments(temp_arg, arg);

								}
								else if (temp_arg.find('=') == string::npos)
								{
									temp_arg.erase(0, 2);
									setArguments(temp_arg, arg);
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

