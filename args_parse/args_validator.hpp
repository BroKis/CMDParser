#pragma once
#include <string>
#include "args_error.hpp"
namespace args_validator
{
	/**
	* @brief Базовый класс-валидатор для валидирования целых чисел
	*/
	class IntValidator
	{
	public:
		virtual ~IntValidator();
		/**
		* @brief Виртуальный метод для проверки целых чисел
		*/
			[[nodiscard]]virtual args_error::ParseResult CheckInt(
			const std::string& fresh_parameter///<Валидируемая строка
		) = 0;
	};
	/**
	* @brief Класс-валидатор наследник для валидирования целых чисел в диапазоне
	*/
	class IntInRangeValidator :public IntValidator
	{
		/**
		* @brief Виртуальный метод для проверки целых чисел в диапазоне
		*/
		
		[[nodiscard]]args_error::ParseResult CheckInt(const std::string& fresh_parameter) override;
	};

	/**
	* @brief Базовый класс-валидатор для валидирования строки
	*/
	class StringValidator
	{
	public:
		virtual ~StringValidator();
		/**
		* @brief Виртуальный метод для проверки строк
		*/
		
		[[nodiscard]]virtual args_error::ParseResult CheckString(const std::string& fresh_parameter) = 0;

	};

	/**
	* @brief Класс-валидатор наследник для валидирования строки
	*/
	class NormalStringValidator : public StringValidator
	{
	public:
		
		/**
		* @brief Метод для проверки строк в нормальной форме без специальных символов
		*/
		[[nodiscard]]args_error::ParseResult CheckString(const std::string& fresh_parameter) override;
	};

	/**
	* @brief Класс-валидатор наследник для валидирования названия текстовых файлов
	*/
	class FileStringValidator :public StringValidator
	{
	public:
		/**
		* @brief Метод для проверки строк на соответствие формату текстовых файлов
		*/
		
		[[nodiscard]] args_error::ParseResult CheckString(const std::string& fresh_parameter) override;
	};
	/**
	* @brief Базовый класс-валидатор для валидирования булевых значений
	*/
	class BoolValidator
	{
	public:
		virtual ~BoolValidator();
		/**
		* @brief Виртуальный метод для проверки строк на соответствие значению истины/ложь
		*/
		
		[[nodiscard]]virtual args_error::ParseResult CheckBool(const std::string& fresh_parameter) = 0;
	};

	/**
	* @brief Класс-валидатор для валидирования булевых значений в нормальной форме
	*/
	class NormalBoolValidator : public BoolValidator
	{
	public:
		/**
		* @brief Метод для проверки строк на соответствие значению истины/ложь
		*/
		
		[[nodiscard]] args_error::ParseResult CheckBool(const std::string& fresh_parameter) override;

	};


	/**
	* @brief Базовый класс-валидатор для валидирования поступающих аргументов для парсинга
	*/
	class ParserValidator
	{
	public:
		virtual ~ParserValidator();
		/**
		* @brief Метод для проверки строк на соответствие аргументов для парсинга 
		*/
		
		[[nodiscard]]virtual args_error::ParseResult CheckInput(const std::string& fresh_parameter) = 0;
	};
	/**
	* @brief Класс-валидатор для валидирования поступающих аргументов для парсинга
	*/
	class NormalParserValidator : public ParserValidator
	{
	public:
		/**
		* @brief Метод для проверки строк на соответствие аргументов для парсинга
		*/
		
		[[nodiscard]]args_error::ParseResult CheckInput(const std::string& fresh_parameter) override;
	};

	

	
}/*namespace args_validator*/
