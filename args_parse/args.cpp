#include "args.hpp"
#include "utils.hpp"
#include <iostream>
#include <algorithm>
namespace args_parse
{
	std::string extractable = "=";

	void EatParams(int argc, const char** argv)
	{
		for (int i = 0; i < argc; ++i)
		{
			std::cout << "[" << i << "]: '" << argv[i] << "'" << std::endl;
		}
	}


	args_error::ParseResult ArgsParser::tryParse(const std::string& parseable_arg)
	{
		return _validator->CheckInput(parseable_arg);
	}

	std::string ArgsParser::extractParameter(const std::string& source, std::string& extractable)
	{
		auto it = std::search(source.begin(), source.end(),
			extractable.begin(), extractable.end());
		std::string argument(it + 1, source.end());
		return argument;
	}

	args_error::ParseResult ArgsParser::setParamsInLongNameWithEqualOrWithout(const std::string& source, Arg* arg, const char** argv, int& index)
	{
		if (source.find('=') == std::string::npos) return arg->SetValue(argv[++index]);
		return arg->SetValue(extractParameter(source, extractable));
	}

	args_error::ParseResult ArgsParser::setParamsInShortNameWithEqual(const std::string& source, Arg* arg)
	{
		if (arg->getType() == ArgumentsType::Empty)
			return args_error::ParseResult::Fail(args_error::Error{ "The argument to which you are trying to assign the parameter is empty" });
		return arg->SetValue(extractParameter(source, extractable));
	}

	args_error::ParseResult ArgsParser::setParamsInShortNameWithoutEqual(const std::string& source, Arg* arg,const char** argv, int& index)
	{

		if (source.find(arg->getShortName()) == source.size() - 1 && arg->getType() != ArgumentsType::Empty)
		{
			return arg->SetValue(argv[++index]);
		}
		if (arg->getType() == ArgumentsType::Empty)
		{
			return arg->SetValue();
		}
		std::string delimeter(1, arg->getShortName());
		return arg->SetValue(extractParameter(source, delimeter));
	}

	args_error::ParseResult ArgsParser::parseLongCommandArgument(const std::string& source, const char** argv, int& index)
	{
		for (const auto& arg : Args)
		{
			std::string findArgument = utils::extractShortFormOfLongName(source);
			if (arg->getLongName() == findArgument || (arg->getLongName().find(findArgument) != std::string::npos && !arg->isDefined()))
			{
				if (const auto result = setParamsInLongNameWithEqualOrWithout(source, arg, argv, index); !result.isOk()) return result;
				if (!arg->isDefined()) arg->setDefinded(true);
			}
		}
		return args_error::ParseResult::Ok();

	}

	args_error::ParseResult ArgsParser::parseShortCommandArgument(const std::string& source, const char** argv, int& index)
	{
		for (const auto& arg : Args)
		{
			if (source.find(arg->getShortName()) != std::string::npos)
			{
				if (source.find('=') != std::string::npos)
				{
					if (const auto result = setParamsInShortNameWithEqual(source, arg); !result.isOk()) return result;
				}
				else
				{
					if (const auto result = setParamsInShortNameWithoutEqual(source, arg, argv, index);  !result.isOk()) return result;
				}
				if (!arg->isDefined()) arg->setDefinded(true);
			}
		}
		return args_error::ParseResult::Ok();
	}
	args_types::Arg* ArgsParser::getArgumentFromVector(int index) const
	{
		if (index < Args.size())
		{
			return Args[index];
		}
		return nullptr;
	}

	void ArgsParser::SetValidator(args_validator::ParserValidator* validator)
	{
		_validator = validator;
	}


	void ArgsParser::add(Arg* arg)
	{
		Args.push_back(arg);
	}

	args_error::ParseResult ArgsParser::parse(int argc, const char** argv)
	{
		for (int i = 1; i < argc; i++)
		{
			std::string temp_arg = argv[i];
			if (const auto result = tryParse(temp_arg); result.isOk())
			{
				if (temp_arg.find("--") == 0)
				{
					if (const auto result = parseLongCommandArgument(temp_arg, argv, i); !result.isOk()) return result;
				}
				else if (temp_arg.find("-") == 0)
				{
					if (const auto result = parseShortCommandArgument(temp_arg, argv, i); !result.isOk())return result;
				}
			}
			else
			{
				return result;
			}
		}
		return args_error::ParseResult::Ok();
	}

	std::string ArgsParser::GetHelp() const
	{
		std::string result = "";

		for (const auto& arg : Args) {
			result += "-";
			result += arg -> getShortName();
			result += " --";
			result += arg->getLongName();
			result += " | ";
			result += arg-> getDescription();
			result += " | ";
			result += utils::enumToString(arg->getType());
			result += "\n";
		}
		return result;
	}
}/* namespace args_parse */

