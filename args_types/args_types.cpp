#include "args_types.hpp"
#include <iostream>

namespace args_types
{
	Arg::Arg(char shortName, const char* longName) : shortName(shortName), longName(longName) {};
	Arg::Arg(const char* longName) : longName(longName) {};

	char Arg::getShortName() const
	{
		return shortName;
	}

	string Arg::getLongName() const
	{
		return longName;
	}

	void Arg::addDescription(const char* desc)
	{
		description = desc;
	}

	string Arg::getDescription() const
	{
		return description;
	}

	IntArg::IntArg(char shortName, const char* longName):Arg(shortName,longName) {}
	IntArg::IntArg(const char* longName):Arg(longName) {}

	BoolArg::BoolArg(char shortName, const char* longName) :Arg(shortName, longName) {}
	BoolArg::BoolArg(const char* longName) :Arg(longName) {}

	StringArg::StringArg(char shortName, const char* longName) :Arg(shortName, longName) {}
	StringArg::StringArg(const char* longName) :Arg(longName) {}


	MultiIntArg::MultiIntArg(char shortName, const char* longName) :Arg(shortName, longName) {}
	MultiIntArg::MultiIntArg(const char* longName) :Arg(longName) {}

	MultiBoolArg::MultiBoolArg(char shortName, const char* longName) :Arg(shortName, longName) {}
	MultiBoolArg::MultiBoolArg(const char* longName) :Arg(longName) {}

	MultiStringArg::MultiStringArg(char shortName, const char* longName) :Arg(shortName, longName) {}
	MultiStringArg::MultiStringArg(const char* longName) :Arg(longName) {}


	int IntArg::getArgument() const
	{
		return argument;
	}

	void IntArg::setArgument(int arg)
	{
		argument = arg;
	}

	int BoolArg::getArgument() const
	{
		return argument;
	}

	void BoolArg::setArgument(int arg)
	{
		argument = arg;
	}

	string StringArg::getArgument() const
	{
		return argument;
	}

	void StringArg::setArgument(const char* arg)
	{
		argument = arg;
	}

	vector<int> MultiIntArg::getArguments() const
	{
		return arguments;

	}

	void MultiIntArg::setArgument(int arg)
	{
		arguments.push_back(arg);
	}

	vector<int> MultiBoolArg::getArguments() const
	{
		return arguments;

	}

	void MultiBoolArg::setArgument(int arg)
	{
		arguments.push_back(arg);
	}

	vector<string> MultiStringArg::getArguments() const
	{
		return arguments;

	}

	void MultiStringArg::setArgument(const char* arg)
	{
		arguments.push_back(arg);
	}


}