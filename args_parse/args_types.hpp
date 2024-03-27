#include <string>
#include <vector>
using namespace std;

namespace args_types
{
	/// @brief ��������� ��� ���������� �������, �������� ���� �������-�����������
	///
	/// �������� ����������� ������
	/// 
	/// @attention 
	/// ��� ������ ���������� � ����� ��������� ����������.
	class Interface
	{
	public:
		/// @brief ����������� ����������
		///
		/// ����� ��������� ����������
		virtual ~Interface() = default;
		/// @brief ����� ��� ���������� ������ ���������
		///
		/// ����������� ����� ��������
		/// 
		/// @attention 
		/// ��������������� ��� ����� ���������� ��������
		virtual void addIntArg(
			/// ������������� ��������
			int arg
		) {}; 

		/// @brief ����� ��� ���������� �������� ���������
		///
		/// ����������� ������� ��������
		/// 
		/// @attention 
		/// ��������������� ��� ����� �������� ������/����
		virtual void addBoolArg(
			///������� ��������
			bool arg
		) {};

		/// @brief ����� ��� ���������� ���������� ���������
		///
		/// ����������� ���������  ��������
		/// 
		virtual void addStringArg(
			///��������� ��������
			string arg
		) {};
		/// @brief ����� ��� ��������� ������ ���������
		///
		/// ���������� ����� �����
		/// 
		/// @attention 
		/// ��������������� ��� ����� ����� ��������
		virtual int getIntArg() const { return 0; };
		virtual bool getBoolArg() const { return false; };
		virtual string getStringArg() const { return ""; };
		
	};
	
	class Arg:public Interface
	{
	private:
		bool isDefine = false;
		string longName;
		char shortName;
		string_view description;
	public:
		Arg(char shortName, string_view longName);
		Arg(string_view longName);
		virtual ~Arg();
		virtual char getShortName() const;
		virtual string getLongName() const;
		virtual void addDescription(const string_view& desc);
		virtual string_view getDescription() const;
		virtual bool isDefined() const;
		virtual void setDefinded(bool flag);
		virtual void showHelp() const {};
		
	};

	class IntArg :public Arg
	{
	private:
		int argument;
	public:
		IntArg(char shortName, string_view longName);
		IntArg(string_view longName);
		void addIntArg(int arg) override;
		int getIntArg() const;
		void showHelp() const override;

	};

	class BoolArg :public Arg
	{
	private:
		bool argument;
	public:
		BoolArg(char shortName, string_view longName);
		BoolArg(string_view longName);
		void addBoolArg(bool arg) override;
		bool getBoolArg() const;
		void showHelp() const override;
	

	};

	class StringArg :public Arg
	{
	private:
		string argument;
	public:
		StringArg(char shortName, string_view longName);
		StringArg(string_view longName);
		void addStringArg(string arg) override;
		string getStringArg() const ;
		void showHelp() const override; 

		
	};

	class MultiIntArg :public Arg
	{
	private:
		vector<int> arguments;
	public:

		MultiIntArg(char shortName, string_view longName);
		MultiIntArg(string_view longName);
		void addIntArg(int arg) override;
		void showHelp() const override;
	
	};

	class MultiBoolArg :public Arg
	{
	private:
		vector<bool> arguments;
	public:
		MultiBoolArg(char shortName, string_view longName);
		MultiBoolArg(string_view longName);
		void addBoolArg(bool arg) override;
		void showHelp() const override;
	
	};

	class MultiStringArg :public Arg
	{
	private:
		vector<string> arguments;
	public:
		MultiStringArg(char shortName, string_view longName);
		MultiStringArg(string_view longName);
		void addStringArg(string arg) override;
		void showHelp() const override;
	};
}