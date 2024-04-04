#pragma once
#include <string>
#include <vector>
#include <string>
#include "args_error.hpp"
#include "args_validator.hpp"


namespace args_types
{
	/** @brief Перечисление типов аргумента
		Перечисление показывающее тип аргумента
	*/
	enum class ArgumentsType {
		Int,///<Целый
		String,///<Строковый
		Bool,///<Булевый
		Empty ///<Пустой
	};

	
	/** @brief Базовый класс от которого наследуются остальные классы
	* Содержит поля и методы, присущие классам-наследникам
	* 
	* @attention 
	* Все методы вирутальны
	*/
	class Arg
	{
	private:
		
		bool isDefine = false;///< Поле обозначающее определен ли аргумент 
		
		std::string longName;///<Поле обозначающее длинное имя аргумента
		
		char shortName;///<Поле обозначающее короткое имя аргумента
		
		std::string_view description;///<Поле обозначающее описание аргумента
		
		ArgumentsType type;///<Поле перечисление для типа аргумента
	public:
		/**@brief Конструктор для аргумента если он содержит короткое и длинное имя
		* Создавется объект класса с коротким и длинным именем
		*/
		Arg(char shortName, std::string_view longName,ArgumentsType type);
		/**@brief Конструктор для аргумента если он содержит длинное имя
		*Создается объект с коротким именем
		*/
		Arg(std::string_view longName, ArgumentsType type);
		/**@brief Виртуальный деструктор для правильной цепочки наследования и удаления объектов*/

		virtual ~Arg();

		/**@brief Метод возвращающий короткое имя аргумента*/
		virtual char getShortName() const;
		/**@brief Метод возвращающий короткое длинное аргумента*/
		virtual std::string getLongName() const;
		/**@brief Метод для добавления описания аргумента*/
		virtual void addDescription(
			
			const std::string_view& desc///<Переменная описания аргумента
		);
		
		virtual std::string_view getDescription() const;///<Метод возвращающий описание аргумента
		
		virtual bool isDefined() const;///<brief Метод возвращающий флаг, определяющий определен аргумент или нет
		
		virtual void setDefinded(bool flag);///<Метод устанавливающий флаг, определен ли аргумент.
		
		virtual void showHelp() const {};///<Метод возвращающий описание аргумента
		
		virtual ArgumentsType getType() const;///<Метод возвращающий тип аргумента
		
		virtual args_error::ParseResult SetValue() = 0;///<Метод устанавливающий значение аргумента, если тот пустой
		
		virtual args_error::ParseResult SetValue(const std::string & param) = 0;///<Метод устанавливающий значение аргумента, если тот не пустой
	};

	/**@brief Класс для целого аргумента
	* Класс отражающий целый аргумент
	*/
	class IntArg :public Arg
	{
	private:
	
		int argument;///< поле-параметр аргумента
		
		args_validator::IntValidator* _validator;///<поле валидатора целых чисел
	public:
		IntArg(char shortName, std::string_view longName, ArgumentsType type);
		IntArg(std::string_view longName, ArgumentsType type);
		args_error::ParseResult SetValue() override;
		args_error::ParseResult SetValue(const std::string& param) override;
		void showHelp() const override;
		/** @brief Метод устанавливающий валидатор целых чисел
		*Устанавливает валидатор целых чисел
		*@attention
		*Подразумевается, что валидатор создан динамическим выделением памяти
		*/
		void SetIntValidator(
			args_validator::IntValidator* validator///<Параметр валидатора для целых чисел
		);

	};

	/** @brief Класс для булевого аргумента
	* Класс отражающий булевый аргумент
	*/
	class BoolArg :public Arg
	{
	private:
		
		bool argument;///<Поле-параметр аргумента
		
		args_validator::BoolValidator* _validator;///<Поле валидатора булевых значений
	public:
		BoolArg(char shortName, std::string_view longName, ArgumentsType type);
		BoolArg(std::string_view longName, ArgumentsType type);
		void showHelp() const override;
		args_error::ParseResult SetValue() override;
		args_error::ParseResult SetValue(const std::string& param) override;
		/** @brief Метод устанавливающий валидатор булевых значени
		*Устанавливает валидатор булевых значений 
		*@attention
		*Подразумевается, что валидатор создан динамическим выделением памяти*/
		void SetBoolValidator(
			args_validator::BoolValidator *validator///<Параметр булевого валидатор
		);

	};
	/** @brief Класс для строкового аргумента
	* Класс отражающий строковый аргумент
	*/
	class StringArg :public Arg
	{
	private:
		
		std::string argument;///<Поле - параметр аргумента
		
		args_validator::StringValidator* _validator;///<Поле валидатора строковых значений
	public:
		StringArg(char shortName, std::string_view longName, ArgumentsType type);
		StringArg(std::string_view longName, ArgumentsType type);
		void showHelp() const override; 
		args_error::ParseResult SetValue() override;
		args_error::ParseResult SetValue(const std::string& param) override;
		/** @brief Метод устанавливающий валидатор строковых значений
		*Устанавливает валидатор стркоковых значений 
		* @attention
		* Подразумевается, что валидатор создан динамическим выделением памяти
		*/
		void SetStringValidator(
			args_validator::StringValidator* validator///<Параметр строкового валидатора
		);
	};

	/** @brief Класс для целого мультиаргумента
	*  Класс для описания мультиаргументов целых чисел
	*/
	class MultiIntArg :public Arg
	{
	private:
		
		std::vector<int> arguments;///<список целых параметров
		
		args_validator::IntValidator* _validator;///<поле валидатора целых чисел для мультиаргумента
	public:
		MultiIntArg(char shortName, std::string_view longName, ArgumentsType type);
		MultiIntArg(std::string_view longName, ArgumentsType type);
		void showHelp() const override;
		args_error::ParseResult SetValue() override;
		args_error::ParseResult SetValue(const std::string& param) override;
		/** @brief Метод устанавливающий валидатор целых значений для мультиаргумента
		* Устанавливает валидатор целых значений для мультиаргумента
		*
		* @attention
		*Подразумевается, что валидатор создан динамическим выделением памяти*/
		void SetIntValidator(
			
			args_validator::IntValidator* validator///<Параметр валидатора целых
		);
	};

	/**@brief  Класс для булевого мультиаргумента
	*  Класс для описания множества булевых мультиаргументов
	*/
	class MultiBoolArg :public Arg
	{
	private:
		
		std::vector<bool> arguments;///<список булевых параметров
		
		args_validator::BoolValidator* _validator;///<поле валидатора булевых значений для мультиаргумента
	public:
		MultiBoolArg(char shortName, std::string_view longName, ArgumentsType type);
		MultiBoolArg(std::string_view longName, ArgumentsType type);
		void showHelp() const override;
		args_error::ParseResult SetValue() override;
		args_error::ParseResult SetValue(const std::string& param) override;
		/**@brief Метод устанавливающий валидатор булевых значений
		*Устанавливает валидатор булевых значений для мультиаргумента
		* 
		*@attention
		*Подразумевается, что валидатор создан динамическим выделением памяти*/
		void SetBoolValidator(
			args_validator::BoolValidator*validator///< Параметр валидатора булевых значений
		);
	
	};

	/** @brief Класс для строкового мультиаргумента
	* Класс для описания множества булевых мультиаргументов
	*/
	class MultiStringArg :public Arg
	{
	private:
		
		std::vector<std::string> arguments;///<список строковых параметров
		
		args_validator::StringValidator* _validator;///<поле валидатора строковых значений для мультиаргумента
	public:
		MultiStringArg(char shortName, std::string_view longName, ArgumentsType type);
		MultiStringArg(std::string_view longName, ArgumentsType type);
		void showHelp() const override;
		args_error::ParseResult SetValue() override;
		args_error::ParseResult SetValue(const std::string& param) override;
		/** Метод устанавливающий валидатор строковых значений
		*Устанавливает валидатор строковых значений для мультиаргумента
		* @attention
		* Подразумевается, что валидатор создан динамическим выделением памяти*/
		void SetStringValidator(
			args_validator::StringValidator* validator///параметр для установки мультиаргумента
		);
	};
}
