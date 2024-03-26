#include <string>
#include <vector>
using namespace std;

namespace args_types
{
	class Interface
	{
	public:
		virtual void addIntArg(int arg) {};
		virtual void addBoolArg(bool arg) {};
		virtual void addStringArg(string arg) {};
	};
	
	class Arg:public Interface
	{
	protected:
		string longName="";
		char shortName;
		string description;
	public:
		Arg(char shortName, string_view longName);
		Arg(string_view longName);
		virtual char getShortName() const;
		virtual string getLongName() const;
		virtual void addDescription(const string& desc);
		virtual string getDescription() const;
		
	};

	class IntArg :public Arg
	{
	protected:
		int argument;
	public:
		IntArg(char shortName, string_view longName);
		IntArg(string_view longName);
		void addIntArg(int arg) override;
	};

	class BoolArg :public Arg
	{
	protected:
		bool argument;
	public:
		BoolArg(char shortName, string_view longName);
		BoolArg(string_view longName);
		void addBoolArg(bool arg) override;
	};

	class StringArg :public Arg
	{
	protected:
		string argument;
	public:
		StringArg(char shortName, string_view longName);
		StringArg(string_view longName);
		void addStringArg(string arg) override;
		
	};

	class MultiIntArg :public Arg
	{
	protected:
		vector<int> arguments;
	public:

		MultiIntArg(char shortName, string_view longName);
		MultiIntArg(string_view longName);
	
	};

	class MultiBoolArg :public Arg
	{
	protected:
		vector<int> arguments;
	public:
		MultiBoolArg(char shortName, string_view longName);
		MultiBoolArg(string_view longName);
	
	};

	class MultiStringArg :public Arg
	{
	protected:
		vector<string> arguments;
	public:
		MultiStringArg(char shortName, string_view longName);
		MultiStringArg(string_view longName);
	
	};
}