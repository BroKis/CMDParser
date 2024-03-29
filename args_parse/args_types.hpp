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
		/// @brief Метод для получения булевого аргумента
		///
		/// Возвращает булевый аргумент
		virtual bool getBoolArg() const { return false; };
		/// @brief Метод для получения строкового аргумента
		///
		/// Возвращает строковый аргумент
		virtual string getStringArg() const { return ""; };
		
	};
	
	/// @brief Базовый класс от которого наследуются остальные классы
	///
	/// Содержит поля и методы, присущие классам-наследникам
	/// 
	/// @attention 
	/// Все методы вирутальны
	class Arg:public Interface
	{
	private:
		/// Поле обозначающее определен ли аргумент 
		bool isDefine = false;
		/// Поле обозначающее длинное имя аргумента
		string longName;
		/// Поле обозначающее короткое имя аргумента
		char shortName;
		/// Поле обозначающее описание аргумента
		string_view description;
	public:
		///@brief Конструктор для аргумента если он содержит короткое и длинное имя
		///
		/// Создавется объект класса с коротким и длинным именем
		Arg(char shortName, string_view longName);
		///@brief Конструктор для аргумента если он содержит длинное имя
		///
		/// Создается объект с коротким именем
		Arg(string_view longName);
		///@brief Виртуальный деструктор для правильной цепочки наследования и удаления объектов

		virtual ~Arg();
		///@brief Метод возвращающий короткое имя аргумента
		virtual char getShortName() const;
		///@brief Метод возвращающий короткое длинное аргумента
		virtual string getLongName() const;
		///@brief Метод для добавления описания аргумента
		virtual void addDescription(
			///Переменная описания аргумента
			const string_view& desc
		);

		///@brief Метод возвращающий описание аргумента
		virtual string_view getDescription() const;
		///@brief Метод возвращающий флаг, определяющий определен аргумент или нет
		virtual bool isDefined() const;
		///@brief Метод устанавливающий флаг, определен ли аргумент.
		virtual void setDefinded(bool flag);
		virtual void showHelp() const {};
		
	};

	/// @brief Класс для целого аргумента
	class IntArg :public Arg
	{
	private:
		/// @brief поле-параметр аргумента
		int argument;
	public:
		IntArg(char shortName, string_view longName);
		IntArg(string_view longName);
		void addIntArg(int arg) override;
		int getIntArg() const;
		void showHelp() const override;

	};

	/// @brief Класс для булевого аргумента
	class BoolArg :public Arg
	{
	private:
		///Поле-параметр аргумента
		bool argument;
	public:
		BoolArg(char shortName, string_view longName);
		BoolArg(string_view longName);
		void addBoolArg(bool arg) override;
		bool getBoolArg() const;
		void showHelp() const override;
	

	};
	/// @brief Класс для строкового аргумента
	class StringArg :public Arg
	{
	private:
		//Поле - параметр аргумента
		string argument;
	public:
		StringArg(char shortName, string_view longName);
		StringArg(string_view longName);
		void addStringArg(string arg) override;
		string getStringArg() const ;
		void showHelp() const override; 

		
	};

	/// @brief Класс для целого мультиаргумента
	class MultiIntArg :public Arg
	{
	private:
		/// список целых параметров
		vector<int> arguments;
	public:

		MultiIntArg(char shortName, string_view longName);
		MultiIntArg(string_view longName);
		void addIntArg(int arg) override;
		void showHelp() const override;
	
	};


	/// @brief Класс для булевого мультиаргумента
	class MultiBoolArg :public Arg
	{
	private:
		/// список булевых параметров
		vector<bool> arguments;
	public:
		MultiBoolArg(char shortName, string_view longName);
		MultiBoolArg(string_view longName);
		void addBoolArg(bool arg) override;
		void showHelp() const override;
	
	};

	/// @brief Класс для строкового мультиаргумента
	class MultiStringArg :public Arg
	{
	private:
		/// список строковых параметров
		vector<string> arguments;
	public:
		MultiStringArg(char shortName, string_view longName);
		MultiStringArg(string_view longName);
		void addStringArg(string arg) override;
		void showHelp() const override;
	};
}
