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
		/**Поле обозначающее определен ли аргумент*/
		bool isDefine = false;
		/**Поле обозначающее длинное имя аргумента*/
		std::string longName{};
		/**Поле обозначающее короткое имя аргумента*/
		char shortName{};
		/**Поле обозначающее описание аргумента*/
		std::string_view description{};
		/**Поле перечисление для типа аргумента*/
		ArgumentsType type{};
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
		/**Метод возвращающий описание аргумента*/
		virtual std::string_view getDescription() const;
		/** @brief Метод возвращающий флаг, определяющий определен аргумент или нет*/
		virtual bool isDefined() const;
		/**Метод устанавливающий флаг, определен ли аргумент.*/
		virtual void setDefinded(bool flag);
		/**Метод возвращающий тип аргумента*/
		virtual ArgumentsType getType() const;
		/**Метод устанавливающий значение аргумента, если тот пустой*/
		virtual args_error::ParseResult SetValue() = 0;
		/**Метод устанавливающий значение аргумента, если тот не пустой*/
		virtual args_error::ParseResult SetValue(const std::string & param) = 0;
	};

	/**@brief Класс для целого аргумента
	* Класс отражающий целый аргумент
	*/
	class IntArg :public Arg
	{
	private:
		///< поле-параметр аргумента
		int argument{};
		///<поле валидатора целых чисел
		args_validator::IntValidator*_validator{};
	public:
		IntArg(char shortName, std::string_view longName, ArgumentsType type);
		IntArg(std::string_view longName, ArgumentsType type);
	
		args_error::ParseResult SetValue() override;
		args_error::ParseResult SetValue(const std::string& param) override;
		const int  GetValue() const;
		/** @brief Метод устанавливающий валидатор целых чисел
		*Устанавливает валидатор целых чисел
		*@attention
		*Подразумевается, что валидатор создан динамическим выделением памяти
		*/
		void SetIntValidator(
			//Параметр валидатора для целых чисе
			args_validator::IntValidator*validatorл
		);

	};

	/** @brief Класс для булевого аргумента
	* Класс отражающий булевый аргумент
	*/
	class BoolArg :public Arg
	{
	private:
		//Поле-параметр аргумента
		bool argument{};
		//Поле валидатора булевых значений
		args_validator::BoolValidator* _validator{};
	public:
		BoolArg(char shortName, std::string_view longName, ArgumentsType type);
		BoolArg(std::string_view longName, ArgumentsType type);
		const bool  GetValue() const;
		args_error::ParseResult SetValue() override;
		args_error::ParseResult SetValue(const std::string& param) override;
		/** @brief Метод устанавливающий валидатор булевых значени
		*Устанавливает валидатор булевых значений 
		*@attention
		*Подразумевается, что валидатор создан динамическим выделением памяти*/
		void SetBoolValidator(
			//Параметр булевого валидатор
			args_validator::BoolValidator *validator
		);

	};
	/** @brief Класс для строкового аргумента
	* Класс отражающий строковый аргумент
	*/
	class StringArg :public Arg
	{
	private:
		//Поле - параметр аргумента
		std::string argument{};
		//Поле валидатора строковых значений
		args_validator::StringValidator* _validator{};
	public:
		StringArg(char shortName, std::string_view longName, ArgumentsType type);
		StringArg(std::string_view longName, ArgumentsType type);
		const std::string  GetValue() const;
		args_error::ParseResult SetValue() override;
		args_error::ParseResult SetValue(const std::string& param) override;
		/** @brief Метод устанавливающий валидатор строковых значений
		*Устанавливает валидатор стркоковых значений 
		* @attention
		* Подразумевается, что валидатор создан динамическим выделением памяти
		*/
		void SetStringValidator(
			//Параметр строкового валидатора
			args_validator::StringValidator* validator
		);
	};

	/** @brief Класс для целого мультиаргумента
	*  Класс для описания мультиаргументов целых чисел
	*/
	class MultiIntArg :public Arg
	{
	private:
		//список целых параметров
		std::vector<int> arguments{};
		//поле валидатора целых чисел для мультиаргумента
		args_validator::IntValidator* _validator{};
	public:
		MultiIntArg(char shortName, std::string_view longName, ArgumentsType type);
		MultiIntArg(std::string_view longName, ArgumentsType type);
		const std::vector<int>  GetValue() const;
		args_error::ParseResult SetValue() override;
		args_error::ParseResult SetValue(const std::string& param) override;
		/** @brief Метод устанавливающий валидатор целых значений для мультиаргумента
		* Устанавливает валидатор целых значений для мультиаргумента
		*
		* @attention
		*Подразумевается, что валидатор создан динамическим выделением памяти*/
		void SetIntValidator(
			//Параметр валидатора целых
			args_validator::IntValidator* validator
		);
	};

	/**@brief  Класс для булевого мультиаргумента
	*  Класс для описания множества булевых мультиаргументов
	*/
	class MultiBoolArg :public Arg
	{
	private:
		//список булевых параметров
		std::vector<bool> arguments{};
		//поле валидатора булевых значений для мультиаргумента
		args_validator::BoolValidator* _validator{};
	public:
		MultiBoolArg(char shortName, std::string_view longName, ArgumentsType type);
		MultiBoolArg(std::string_view longName, ArgumentsType type);
		const std::vector<bool>  GetValue() const;
		args_error::ParseResult SetValue() override;
		args_error::ParseResult SetValue(const std::string& param) override;
		/**@brief Метод устанавливающий валидатор булевых значений
		*Устанавливает валидатор булевых значений для мультиаргумента
		* 
		*@attention
		*Подразумевается, что валидатор создан динамическим выделением памяти*/
		void SetBoolValidator(
			//Параметр валидатора булевых значений
			args_validator::BoolValidator*validator
		);
	
	};

	/** @brief Класс для строкового мультиаргумента
	* Класс для описания множества булевых мультиаргументов
	*/
	class MultiStringArg :public Arg
	{
	private:
		//список строковых параметров
		std::vector<std::string> arguments{};
		//поле валидатора строковых значений для мультиаргумента
		args_validator::StringValidator* _validator{};
	public:
		MultiStringArg(char shortName, std::string_view longName, ArgumentsType type);
		MultiStringArg(std::string_view longName, ArgumentsType type);
		const std::vector<std::string>  GetValue() const;
		args_error::ParseResult SetValue() override;
		args_error::ParseResult SetValue(const std::string& param) override;
		/** Метод устанавливающий валидатор строковых значений
		*Устанавливает валидатор строковых значений для мультиаргумента
		* @attention
		* Подразумевается, что валидатор создан динамическим выделением памяти*/
		void SetStringValidator(
			//параметр для установки мультиаргумента
			args_validator::StringValidator* validator
		);
	};
}/*namespace args_types*/
