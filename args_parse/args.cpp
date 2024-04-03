#include "args.hpp"
#include <iostream>
#include <algorithm>
namespace args_parse
{
	
	ArgsParser::ArgsParser() {};
	
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

	args_error::ParseResult ArgsParser::setParamsInLongNameWithEqual(const std::string& source, std::unique_ptr<Arg>const& arg, const char** argv, int &index)
	{
		 
		if (source.find('=') != std::string::npos)
		{
			return arg->SetValue(extractParameter(source, extractable));
		}
		else
		{
			return arg->SetValue(argv[++index]);
		}
		
	}

	args_error::ParseResult ArgsParser::setParamsInShortNameWithEqual(const std::string& source, std::unique_ptr<Arg>const& arg)
	{
		
		if (arg->getType() != ArgumentsType::Empty)
		{
			return arg->SetValue(extractParameter(source, extractable));
		}
		else { return args_error::ParseResult::Fail(args_error::Error{ "The argument to which you are trying to assign the parameter is empty" }); }
		
	}

	args_error::ParseResult ArgsParser::setParamsInShortNameWithoutEqual(const std::string& source, std::unique_ptr<Arg>const& arg, const char** argv, int&index)
	{
		if (source.find(arg->getShortName()) == source.size() - 1 && arg->getType() != ArgumentsType::Empty)
		{
			return arg ->SetValue(argv[++index]);
		}
		else if (arg->getType() != ArgumentsType::Empty)
		{
			std::string delimeter(1, arg->getShortName());
			return arg->SetValue(extractParameter(source, delimeter));
		}
		else
		{
			return arg->SetValue();
		}
		
	}

	args_error::ParseResult ArgsParser::parseLongNameArgument(const std::string& source, const char** argv, int& index)
	{
		for (const auto& arg : Args)
		{
			if (source.find(arg->getLongName()) == 0)
			{
				if (const auto result = setParamsInLongNameWithEqual(source, arg, argv, index); !result.isOk()) return result;
				if(!arg->isDefined()) arg->setDefinded(true);
			}
			return args_error::ParseResult::Fail(args_error::Error{ "The argument you are trying to process is parse" });
		}
		return args_error::ParseResult::Ok();

	}

	args_error::ParseResult ArgsParser::parseShortNameArgument(const std::string& source, const char** argv, int &index)
	{
		for (const auto& arg : Args)
		{
			if (source.find(arg->getShortName()) != std::string::npos)
			{
				if (source.find('=') != std::string::npos )
				{
					if(const auto result = setParamsInShortNameWithEqual(source, arg); !result.isOk()) return result;	
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
	std::unique_ptr<Arg> ArgsParser::getArgumentFromVector(int index)
	{
		if (index < Args.size())
		{
			return std::move(Args[index]);
		}
		return nullptr;
	}

	void ArgsParser::SetValidator(args_validator::ParserValidator* validator)
	{
		_validator = validator;
	}


	void ArgsParser::add(std::unique_ptr<Arg>ptr)
	{
		Args.push_back(std::move(ptr));
	}

	args_error::ParseResult ArgsParser::parse(int argc, const char** argv)
	{
		for (int i = 1; i < argc; i++)
		{
			std::string temp_arg = argv[i];
			if (const auto result = tryParse(temp_arg); result.isOk())
			{
				if (temp_arg.find("--") != std::string::npos)
				{
					if (const auto result = parseLongNameArgument(temp_arg, argv, i); !result.isOk()) return result;
				}
				else if (temp_arg.find("-") != std::string::npos)
				{
					if (const auto result = parseShortNameArgument(temp_arg, argv, i); !result.isOk())return result;
				}
			}
			else
			{
				return result;
			}
		}
		return args_error::ParseResult::Ok();
	}
}/* namespace args_parse */

