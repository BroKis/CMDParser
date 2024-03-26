#include <string>
#include <vector>
using namespace std;

namespace args_types
{
	
	class Arg
	{
	protected:
		string longName;
		char shortName;
		string description;

	public:
		Arg(char shortName, const char* longName);
		Arg(const char* longName);
		virtual char getShortName() const;
		virtual string getLongName() const;
		virtual void addDescription(const char* desc);
		virtual string getDescription() const;
	};

	class IntArg :public Arg
	{
	protected:
		int argument;
	public:
		IntArg(char shortName, const char* longName);
		IntArg(const char* longName);
		void setArgument(int arg);
		int getArgument() const;
	};

	class BoolArg :public Arg
	{
	protected:
		int argument;
	public:
		BoolArg(char shortName, const char* longName);
		BoolArg(const char* longName);
		void setArgument(int arg);
		int getArgument() const;
	};

	class StringArg :public Arg
	{
	protected:
		string argument;
	public:
		StringArg(char shortName, const char* longName);
		StringArg(const char* longName);
		void setArgument(const char* arg);
		string getArgument() const;
	};

	class MultiIntArg :public Arg
	{
	protected:
		vector<int> arguments;
	public:

		MultiIntArg(char shortName, const char* longName);
		MultiIntArg(const char* longName);
		void setArgument(int arg);
		vector<int> getArguments() const;
	};

	class MultiBoolArg :public Arg
	{
	protected:
		vector<int> arguments;
	public:
		MultiBoolArg(char shortName, const char* longName);
		MultiBoolArg(const char* longName);
		void setArgument(int arg);
		vector<int> getArguments() const;
	};

	class MultiStringArg :public Arg
	{
	protected:
		vector<string> arguments;
	public:
		MultiStringArg(char shortName, const char* longName);
		MultiStringArg(const char* longName);
		void setArgument(const char* arg);
		vector<string> getArguments() const;
	};
}