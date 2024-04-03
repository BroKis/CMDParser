#include <string>
#include <vector>
#include <string>
#include "args_error.hpp"
#include "args_validator.hpp"


namespace args_types
{

	enum class ArgumentsType {
		Int,
		String,
		Bool,
		Empty
	};

	
	/// @brief Базовый класс от которого наследуются остальные классы
	///
	/// Содержит поля и методы, присущие классам-наследникам
	/// 
	/// @attention 
	/// Все методы вирутальны
	class Arg
	{
	private:
		/// Поле обозначающее определен ли аргумент 
		bool isDefine = false;
		/// Поле обозначающее длинное имя аргумента
		std::string longName;
		/// Поле обозначающее короткое имя аргумента
		char shortName;
		/// Поле обозначающее описание аргумента
		std::string_view description;
		/// Поле перечисление для типа аргумента
		ArgumentsType type;
	public:
		///@brief Конструктор для аргумента если он содержит короткое и длинное имя
		///
		/// Создавется объект класса с коротким и длинным именем
		Arg(char shortName, std::string_view longName,ArgumentsType type);
		///@brief Конструктор для аргумента если он содержит длинное имя
		///
		/// Создается объект с коротким именем
		Arg(std::string_view longName, ArgumentsType type);
		///@brief Виртуальный деструктор для правильной цепочки наследования и удаления объектов

		virtual ~Arg();

		///@brief Метод возвращающий короткое имя аргумента
		virtual char getShortName() const;
		///@brief Метод возвращающий короткое длинное аргумента
		virtual std::string getLongName() const;
		///@brief Метод для добавления описания аргумента
		virtual void addDescription(
			///Переменная описания аргумента
			const std::string_view& desc
		);
		///@brief Метод возвращающий описание аргумента
		virtual std::string_view getDescription() const;
		///@brief Метод возвращающий флаг, определяющий определен аргумент или нет
		virtual bool isDefined() const;
		///@brief Метод устанавливающий флаг, определен ли аргумент.
		virtual void setDefinded(bool flag);
		///@brief Метод возвращающий описание аргумента
		virtual void showHelp() const {};
		///@brief Метод возвращающий тип аргумента
		virtual ArgumentsType getType() const;
		virtual args_error::ParseResult SetValue() = 0;
		virtual args_error::ParseResult SetValue(const std::string & param) = 0;

		
	};

	/// @brief Класс для целого аргумента
	class IntArg :public Arg
	{
	private:
		/// @brief поле-параметр аргумента
		int argument;
		args_validator::IntValidator* _validator;
	public:
		IntArg(char shortName, std::string_view longName, ArgumentsType type);
		IntArg(std::string_view longName, ArgumentsType type);
		args_error::ParseResult SetValue() override;
		args_error::ParseResult SetValue(const std::string& param) override;
		int getIntParam() const;
		void showHelp() const override;
		void SetIntValidator(args_validator::IntValidator* validator);

	};

	/// @brief Класс для булевого аргумента
	class BoolArg :public Arg
	{
	private:
		///Поле-параметр аргумента
		bool argument;
		args_validator::BoolValidator* _validator;
	public:
		BoolArg(char shortName, std::string_view longName, ArgumentsType type);
		BoolArg(std::string_view longName, ArgumentsType type);
		bool getBoolParam() const;
		void showHelp() const override;
		args_error::ParseResult SetValue() override;
		args_error::ParseResult SetValue(const std::string& param) override;
		void SetBoolValidator(args_validator::BoolValidator *validator);

	};
	/// @brief Класс для строкового аргумента
	class StringArg :public Arg
	{
	private:
		//Поле - параметр аргумента
		std::string argument;
		args_validator::StringValidator* _validator;
	public:
		StringArg(char shortName, std::string_view longName, ArgumentsType type);
		StringArg(std::string_view longName, ArgumentsType type);
		void showHelp() const override; 
		args_error::ParseResult SetValue() override;
		args_error::ParseResult SetValue(const std::string& param) override;
		void SetStringValidator(args_validator::StringValidator* validator);

		
	};

	/// @brief Класс для целого мультиаргумента
	class MultiIntArg :public Arg
	{
	private:
		/// список целых параметров
		std::vector<int> arguments;
		args_validator::IntValidator* _validator;
	public:
		MultiIntArg(char shortName, std::string_view longName, ArgumentsType type);
		MultiIntArg(std::string_view longName, ArgumentsType type);
		void showHelp() const override;
		args_error::ParseResult SetValue() override;
		args_error::ParseResult SetValue(const std::string& param) override;
		void SetIntValidator(args_validator::IntValidator* validator);
	};

	/// @brief Класс для булевого мультиаргумента
	class MultiBoolArg :public Arg
	{
	private:
		/// список булевых параметров
		std::vector<bool> arguments;
		args_validator::BoolValidator* _validator;
	public:
		MultiBoolArg(char shortName, std::string_view longName, ArgumentsType type);
		MultiBoolArg(std::string_view longName, ArgumentsType type);
		void showHelp() const override;
		args_error::ParseResult SetValue() override;
		args_error::ParseResult SetValue(const std::string& param) override;
		void SetBoolValidator(args_validator::BoolValidator*validator);
	
	};

	/// @brief Класс для строкового мультиаргумента
	class MultiStringArg :public Arg
	{
	private:
		/// список строковых параметров
		std::vector<std::string> arguments;
		args_validator::StringValidator* _validator;
	public:
		MultiStringArg(char shortName, std::string_view longName, ArgumentsType type);
		MultiStringArg(std::string_view longName, ArgumentsType type);
		void showHelp() const override;
		args_error::ParseResult SetValue() override;
		args_error::ParseResult SetValue(const std::string& param) override;
		void SetStringValidator(args_validator::StringValidator* validator);
	};
}
