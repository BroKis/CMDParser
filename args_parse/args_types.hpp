#include <string>
#include <vector>
using namespace std;

namespace args_types
{
	/// @brief Интерфейс для реализации методов, присущих всем классам-наследникам
	///
	/// Содержит виртуальные методы
	/// 
	/// @attention 
	/// Все методы вирутальны и имеют начальную реализацию.
	class Interface
	{
	public:
		/// @brief Виртуальный деструктор
		///
		/// Имеет дефолтную реализацию
		virtual ~Interface() = default;
		/// @brief Метод для добавления целого аргумента
		///
		/// Добавляется целый аргумент
		/// 
		/// @attention 
		/// Подразумевается что имеет корректное значение
		virtual void addIntArg(
			/// Целочисленный аргумент
			int arg
		) {}; 

		/// @brief Метод для добавления булевого аргумента
		///
		/// Добавляется булевый аргумент
		/// 
		/// @attention 
		/// Подразумевается что имеет значение Истина/Ложь
		virtual void addBoolArg(
			///Булевый аргумент
			bool arg
		) {};

		/// @brief Метод для добавления строкового аргумента
		///
		/// Добавляется строковый  аргумент
		/// 
		virtual void addStringArg(
			///строковый аргумент
			string arg
		) {};
		/// @brief Метод для получения целого аргумента
		///
		/// Возвращает целое число
		/// 
		/// @attention 
		/// Подразумевается что имеет целое значение
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
