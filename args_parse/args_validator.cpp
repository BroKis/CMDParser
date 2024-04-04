#include "args_validator.hpp"

#include <regex>
namespace args_validator
{
	
	args_error::ParseResult IntInRangeValidator::CheckInt(const std::string& fresh_parameter)
	{
		std::regex pattern("^(?:[1-9]|[1-9][0-9]{1,2}|999)$");
		if (std::regex_match(fresh_parameter, pattern)) { return args_error::ParseResult::Ok(); }
		return args_error::ParseResult::Fail(args_error::Error{ "The string is not a number or is outside of acceptable values. Incorrect value:"+fresh_parameter });
	}
	args_error::ParseResult NormalStringValidator::CheckString(const std::string& fresh_parameter)
	{
		std::regex pattern("^[^/@0-9]*$");
		if (std::regex_match(fresh_parameter, pattern)) { return args_error::ParseResult::Ok(); }
		return args_error::ParseResult::Fail(args_error::Error{ "The string contains special characters or numbers. Incorrect value:" + fresh_parameter });
	}
	args_error::ParseResult FileStringValidator::CheckString(const std::string& fresh_parameter)
	{
		std::regex pattern("^.*\\.txt$");
		if (std::regex_match(fresh_parameter, pattern)) { return args_error::ParseResult::Ok(); }
		return args_error::ParseResult::Fail(args_error::Error{ "The string is not the name of the txt file. Incorrect value:" + fresh_parameter });
	}
	args_error::ParseResult NormalBoolValidator::CheckBool(const std::string& fresh_parameter)
	{
		std::regex pattern("^(true|false|0|1)$");
		if (std::regex_match(fresh_parameter, pattern)) { return args_error::ParseResult::Ok(); }
		return args_error::ParseResult::Fail(args_error::Error{ "Was it expected to be true or false with a token or 0 / 1. Incorrect value:" + fresh_parameter });
	}
	args_error::ParseResult NormalParserValidator::CheckInput(const std::string& fresh_parameter)
	{
		std::regex pattern("^((\\-([a-z])=?(\\w\\S*)?)|(\\-{2}([a-z]{2,}(=\\w\\S*)?)))$");
		if (std::regex_match(fresh_parameter, pattern)) { return args_error::ParseResult::Ok();}
		 return args_error::ParseResult::Fail(args_error::Error{ "Wrong argument. Incorrect value:" + fresh_parameter });
	}
	IntValidator::~IntValidator()
	{
	}
	StringValidator::~StringValidator()
	{
	}
	BoolValidator::~BoolValidator()
	{
	}
	ParserValidator::~ParserValidator()
	{
	}
}