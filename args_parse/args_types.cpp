#include "args_types.hpp"
#include <iostream>

namespace args_types
{
	Arg::Arg(char shortName, string_view longName) : shortName(shortName), longName(longName) {}
	Arg::Arg(string_view longName) : longName(longName) {}

	char Arg::getShortName() const
	{
		return shortName;
	}

	string Arg::getLongName() const
	{
		return longName;
	}

	void Arg::addDescription(const string& desc)
	{
		description = desc;
	}

	string Arg::getDescription() const
	{
		return description;
	}

	IntArg::IntArg(char shortName, string_view longName):Arg(shortName,longName) {}
	IntArg::IntArg(string_view longName):Arg(longName) {}

	BoolArg::BoolArg(char shortName, string_view longName) :Arg(shortName, longName) {}
	BoolArg::BoolArg(string_view longName) :Arg(longName) {}

	StringArg::StringArg(char shortName, string_view longName) :Arg(shortName, longName) {}
	StringArg::StringArg(string_view longName) :Arg(longName) {}


	MultiIntArg::MultiIntArg(char shortName, string_view longName) :Arg(shortName, longName) {}
	MultiIntArg::MultiIntArg(string_view longName) :Arg(longName) {}

	MultiBoolArg::MultiBoolArg(char shortName, string_view longNamee) :Arg(shortName, longName) {}
	MultiBoolArg::MultiBoolArg(string_view longName) :Arg(longName) {}

	MultiStringArg::MultiStringArg(char shortName, string_view longName) :Arg(shortName, longName) {}
	MultiStringArg::MultiStringArg(string_view longName) :Arg(longName) {}

	void IntArg::addIntArg(int arg)
	{
		argument = arg;
	}

	void BoolArg::addBoolArg(bool arg)
	{
		argument = arg;
	}

	void StringArg::addStringArg(const string arg)
	{
		argument = arg;
	}
	


}