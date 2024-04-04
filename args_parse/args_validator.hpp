#pragma once
#include <string>
#include "args_error.hpp"
namespace args_validator
{
	class IntValidator
	{
	public:
		virtual ~IntValidator();
		[[discard]]
		virtual args_error::ParseResult CheckInt(const std::string& fresh_parameter) = 0;
	};
	class IntInRangeValidator :public IntValidator
	{
		~IntInRangeValidator() {};
		[[discard]]
		args_error::ParseResult CheckInt(const std::string& fresh_parameter) override;
	};

	class StringValidator
	{
	public:
		virtual ~StringValidator();
		[[discard]]
		virtual args_error::ParseResult CheckString(const std::string& fresh_parameter) = 0;

	};

	class NormalStringValidator : public StringValidator
	{
	public:
		[[discard]]
		args_error::ParseResult CheckString(const std::string& fresh_parameter) override;
	};

	class FileStringValidator :public StringValidator
	{
	public:
		[[discard]]
		args_error::ParseResult CheckString(const std::string& fresh_parameter) override;
	};

	class BoolValidator
	{
	public:
		virtual ~BoolValidator();
		[[discard]]
		virtual args_error::ParseResult CheckBool(const std::string& fresh_parameter) = 0;
	};

	class NormalBoolValidator : public BoolValidator
	{
	public:
		[[discard]]
		args_error::ParseResult CheckBool(const std::string& fresh_parameter) override;

	};

	class ParserValidator
	{
	public:
		virtual ~ParserValidator();
		[[discard]]
		virtual args_error::ParseResult CheckInput(const std::string& fresh_parameter) = 0;
	};

	class NormalParserValidator : public ParserValidator
	{
	public:
		args_error::ParseResult CheckInput(const std::string& fresh_parameter) override;
	};

	

	
}
