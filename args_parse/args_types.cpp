#include "args_types.hpp"
#include <iostream>

namespace args_types
{
	Arg::Arg(char shortName, string_view longName) : shortName(shortName), longName(longName) {}
	Arg::Arg(string_view longName) : longName(longName) {}
	Arg::~Arg()
	{
		isDefine = true;
		longName.clear();
		shortName = '\0';
		description = "";
	}

	char Arg::getShortName() const
	{
		return shortName;
	}

	string Arg::getLongName() const
	{
		return longName;
	}

	void Arg::addDescription(const string_view& desc)
	{
		description = desc;
	}

	string_view Arg::getDescription() const
	{
		return description;
	}

	IntArg::IntArg(char shortName, string_view longName) :Arg(shortName, longName) { }
	IntArg::IntArg(string_view longName) :Arg(longName) {  }

	BoolArg::BoolArg(char shortName, string_view longName) :Arg(shortName, longName) {  }
	BoolArg::BoolArg(string_view longName) :Arg(longName) {  }

	StringArg::StringArg(char shortName, string_view longName) :Arg(shortName, longName) {  }
	StringArg::StringArg(string_view longName) :Arg(longName) {  }


	MultiIntArg::MultiIntArg(char shortName, string_view longName) :Arg(shortName, longName) {  }
	MultiIntArg::MultiIntArg(string_view longName) :Arg(longName) {  }

	MultiBoolArg::MultiBoolArg(char shortName, string_view longName) :Arg(shortName, longName) {  }
	MultiBoolArg::MultiBoolArg(string_view longName) :Arg(longName) {  }

	MultiStringArg::MultiStringArg(char shortName, string_view longName) :Arg(shortName, longName) {  }
	MultiStringArg::MultiStringArg(string_view longName) :Arg(longName) {  }

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

	int IntArg::getIntArg() const
	{
		return argument;
	}
	bool BoolArg::getBoolArg() const
	{
		return argument;
	}

	string StringArg::getStringArg() const
	{
		return argument;
	}



	void MultiIntArg::addIntArg(int arg)
	{
		arguments.push_back(arg);
	}

	void MultiBoolArg::addBoolArg(bool arg) {
		arguments.push_back(arg);
	}

	void MultiStringArg::addStringArg(string arg)
	{
		arguments.push_back(arg);
	}

	void Arg::setDefinded(bool flag)
	{
		isDefine = flag;
	}
	bool Arg::isDefined() const
	{
		return isDefine;
	}

	void IntArg::showHelp() const
	{
		cout << "Name of argument:" << getLongName() << ".Parameter:" << argument << endl;
	}

	void BoolArg::showHelp() const
	{
		cout << "Name of argument:" << getLongName() << ".Parameter:" << argument << endl;
	}

	void StringArg::showHelp() const
	{
		cout << "Name of argument:" << getLongName() << ".Parameter:" << argument << endl;
	}

	void MultiIntArg::showHelp() const
	{
		cout << "Name of argument:" << getLongName() << ".Parameters:";
		for (const auto& arg : arguments)
		{
			cout << arg << " ";
		}
	}

	void MultiBoolArg::showHelp() const
	{
		cout << "Name of argument:" << getLongName() << ".Parameters:";
		for (const auto& arg : arguments)
		{
			cout << arg << " ";
		}
	}

	void MultiStringArg::showHelp() const
	{
		cout << "Name of argument:" << getLongName() << ".Parameters:";
		for (const auto& arg : arguments)
		{
			cout << arg << " ";
		}
	}

}