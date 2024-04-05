#include "args_types.hpp"
#include <iostream>
#include "utils.hpp"

namespace args_types
{

	
	Arg::Arg(char shortName, std::string_view longName, ArgumentsType type) : shortName(shortName), longName(longName), type(type) {}
	Arg::Arg(std::string_view longName, ArgumentsType type) : longName(longName), type(type) {}
	Arg::~Arg(){}
	

	char Arg::getShortName() const
	{
		return shortName;
	}

	std::string Arg::getLongName() const
	{
		return longName;
	}

	void Arg::addDescription(const std::string_view& desc)
	{
		description = desc;
	}

	std::string_view Arg::getDescription() const
	{
		return description;
	}

	ArgumentsType Arg::getType() const
	{
		return type;
	}

	void Arg::setDefinded(bool flag)
	{
		isDefine = flag;
	}
	bool Arg::isDefined() const
	{
		return isDefine;
	}

	
	IntArg::IntArg(char shortName, std::string_view longName, ArgumentsType type) :Arg(shortName, longName, type) { }
	IntArg::IntArg(std::string_view longName, ArgumentsType type) :Arg(longName, type) {  }

	args_error::ParseResult IntArg::SetValue(const std::string& param)
	{
		if (const auto result = _validator->CheckInt(param); result.isOk())
		{
			argument = stoi(param);
			return result;
		}
		else { return result; }
		
	}

	args_error::ParseResult IntArg::SetValue() {
		argument = 0;
		return args_error::ParseResult::Ok();
	}

	void IntArg::SetIntValidator(args_validator::IntValidator* validator)
	{
		_validator = validator;
	}
	
	const int IntArg::GetValue() const
	{
		return argument;
	}

	BoolArg::BoolArg(char shortName, std::string_view longName, ArgumentsType type) :Arg(shortName, longName, type) {  }
	BoolArg::BoolArg(std::string_view longName, ArgumentsType type) :Arg(longName, type) {  }
	

	args_error::ParseResult BoolArg::SetValue()
	{
			argument = 0;
			return args_error::ParseResult::Ok();
	}

	args_error::ParseResult BoolArg::SetValue(const std::string& param)
	{
		if (const auto result = _validator->CheckBool(param); result.isOk())
		{
			argument = utils::Utils::stringToBool(param);
			return result;
		}
		else { return result; }
	}

	void BoolArg::SetBoolValidator(args_validator::BoolValidator* validator)
	{
		_validator = validator;
	}

	const bool BoolArg::GetValue() const
	{
		return argument;
	}


	StringArg::StringArg(char shortName, std::string_view longName, ArgumentsType type) :Arg(shortName, longName, type) {  }
	StringArg::StringArg(std::string_view longName, ArgumentsType type) :Arg(longName, type) {  }

	args_error::ParseResult StringArg::SetValue()
	{
		argument = "";
		return args_error::ParseResult::Ok();
	}

	args_error::ParseResult StringArg::SetValue(const std::string& param)
	{
		if (const auto result = _validator->CheckString(param); result.isOk())
		{
			argument = param;
			return result;
		}
		else { return result; }
	}

	void StringArg::SetStringValidator(args_validator::StringValidator*validator)
	{
		_validator = validator;
	}

	const std::string StringArg::GetValue() const
	{
		return argument;
	}


	MultiIntArg::MultiIntArg(char shortName, std::string_view longName, ArgumentsType type) :Arg(shortName, longName, type) {  }
	MultiIntArg::MultiIntArg(std::string_view longName, ArgumentsType type) :Arg(longName, type) {  }

	args_error::ParseResult MultiIntArg::SetValue(const std::string& param)
	{
		if (const auto result = _validator->CheckInt(param); result.isOk())
		{
			arguments.push_back(stoi(param));
			return result;
		}
		else { return result; }
	}

	args_error::ParseResult MultiIntArg::SetValue()
	{
		arguments.push_back(0);
		return args_error::ParseResult::Ok();
	}

	

	void MultiIntArg::SetIntValidator(args_validator::IntValidator* validator)
	{
		_validator = validator;
	}
	const std::vector<int> MultiIntArg::GetValue() const
	{
		return arguments;
	}


	MultiBoolArg::MultiBoolArg(char shortName, std::string_view longName, ArgumentsType type) :Arg(shortName, longName, type) {  }
	MultiBoolArg::MultiBoolArg(std::string_view longName, ArgumentsType type) :Arg(longName, type) {  }

	args_error::ParseResult MultiBoolArg::SetValue(const std::string& param)
	{
		if (const auto result = _validator->CheckBool(param); result.isOk())
		{
			arguments.push_back(utils::Utils::stringToBool(param));
			return result;
		}
		else { return result; }
	}

	args_error::ParseResult MultiBoolArg::SetValue()
	{
		arguments.push_back(1);
		return args_error::ParseResult::Ok();
	}

	

	void MultiBoolArg::SetBoolValidator(args_validator::BoolValidator* validator)
	{
		_validator = validator;
	}
	const std::vector<bool> MultiBoolArg::GetValue() const
	{
		return arguments;
	}

	MultiStringArg::MultiStringArg(char shortName, std::string_view longName, ArgumentsType type) :Arg(shortName, longName,type) {  }
	MultiStringArg::MultiStringArg(std::string_view longName, ArgumentsType type) :Arg(longName,type) {  }

	args_error::ParseResult MultiStringArg::SetValue(const std::string& param)
	{
		if (const auto result = _validator->CheckString(param); result.isOk())
		{
			arguments.push_back(param);
			return result;
		}
		else { return result; }
	}

	args_error::ParseResult MultiStringArg::SetValue()
	{
		arguments.push_back("");
		return args_error::ParseResult::Ok();
	}

	

	void MultiStringArg::SetStringValidator(args_validator::StringValidator* validator)
	{
		_validator = validator;
	}

	const std::vector<std::string> MultiStringArg::GetValue() const
	{
		return arguments;
	}

}