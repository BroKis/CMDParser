#pragma once
#include <string>
#include "args_error.hpp"
#include <regex>

namespace args_validator
{
	
	/**
	* @brief Шаблонный класс базового валидатора
	*/
	template<typename T>
	class Validator
	{
	public:
		virtual ~Validator() = default;
		/**
		*@brief Метод, проверящий входное значение на соответствие
		*/
		[[nodiscard]] virtual args_error::ParseResult check(const T&) = 0;
	};

	/**
	* @brief Класс валидатор чисел
	* Проверяет находятся ли число в диапазоне от @a _min до @a _max
	*/
	template<typename T>
	class InRangeValidator : public Validator<T>
	{
	private:
		/// Поле хранящее левую границу диапазона
		T _min;
		/// Поле хранящее правую границу диапазона
		T _max;
	public:
		InRangeValidator(T min, T max) :_min{ min }, _max{ max } {}
		[[nodiscard]] args_error::ParseResult check(const T& v) override
		{
			if (v < _min) return args_error::ParseResult::Fail({ "In " + std::to_string(v) + ": value is less than [" + std::to_string(_min) + ";" + std::to_string(_max) + "]" });
			if (v > _max) return args_error::ParseResult::Fail({ "In " + std::to_string(v) + ": value is greater than [" + std::to_string(_min) + ";" + std::to_string(_max) + "]" });
			return args_error::ParseResult::Ok();
		}
		
	};

	/**
	*@brief Класс валидатора для строк
	* 
	*/
	template<typename T = std::string>
	class NormalStringValidator : public Validator<T>
	{
	private:
		/// Поле,хранящее строку с запрещенными символами
		T _forbidden{};
	public:
		NormalStringValidator(T forbidden) : _forbidden{ forbidden } {};
		[[nodiscard]] args_error::ParseResult check(const T& v) override {
			static std::regex pattern("^[^" +_forbidden+"]*$");
			if (std::regex_match(v, pattern)) { return args_error::ParseResult::Ok(); }
			return args_error::ParseResult::Fail(args_error::Error{ "The string contains special characters or numbers. Incorrect value:" + v });
		}
	};

	/**
	*@brief Класс валидатора булевого значения
	*
	*/
	template<typename T>
	class NormalBoolValidator : public Validator<T>
	{
	private:
		
	public:
		NormalBoolValidator() = default;
		[[nodiscard]] args_error::ParseResult check(const T& v) override {
			static std::regex pattern("^(true|false|0|1)$");
			if (std::regex_match(v, pattern)) { return args_error::ParseResult::Ok(); }
			return args_error::ParseResult::Fail(args_error::Error{ "The string contains special characters or numbers. Incorrect value:" + v });
		}
	};

	/**
	*@brief Класс валидатора названия файлов
	*
	*/
	template<typename T>
	class NormalFileValidator : public Validator<T>
	{
	private:
		/// Поле хранящее расширение файла
		T _fileExt;
	public:
		NormalFileValidator(T fileExt) : _fileExt{ fileExt } {};
		[[nodiscard]] args_error::ParseResult check(const T& v) override {
			static std::regex pattern("^.*\\"+_fileExt+"$");
			if (std::regex_match(v, pattern)) { return args_error::ParseResult::Ok(); }
			return args_error::ParseResult::Fail(args_error::Error{ "The string is not the name of the file. Incorrect value:" + v });
		}
	};

	/**
	*@brief Класс валидатора названия файлов
	*
	*/
	template<typename T>
	class NormalPathValidator : public Validator<T>
	{
	private:
	public:
		[[nodiscard]] args_error::ParseResult check(const T& v) override {
			static std::regex pattern("^([A-Za-z]:\\\\)((?:.*\\\\)?)$");
			if (std::regex_match(v, pattern)) { return args_error::ParseResult::Ok(); }
			return args_error::ParseResult::Fail(args_error::Error{ "The string is not the name of the file. Incorrect value:" + v });
		}
	};


	/**
	*@brief Класс валидатора для парсера
	*
	*/
	template<typename T>
	class NormalParserValidator :public Validator<T>
	{
	public:
		NormalParserValidator() = default;
		[[nodiscard]] args_error::ParseResult check(const T& v) override {
			static std::regex pattern("^((\\-([a-z])=?(-?\\w\\S*)?)|(\\-{2}([a-z]{2,}(=-?\\w\\S*)?)))$");
			if (std::regex_match(v, pattern)) { return args_error::ParseResult::Ok(); }
			return args_error::ParseResult::Fail(args_error::Error{ "Wrong argument. Incorrect value:" + v });
		}
	};
	
	/**
	*@brief Класс валидатора для пользовательского типа времени
	*
	*/
	template<typename T>
	class NormalChronoValidator :public Validator<T>
	{
	public:
		NormalChronoValidator() = default;
		[[nodiscard]] args_error::ParseResult check(const T& v) override {
			static std::regex pattern("^[0-9]+(d|h|m|s|ms|us|ns)$");
			if (std::regex_match(v, pattern)) { return args_error::ParseResult::Ok(); }
			return args_error::ParseResult::Fail(args_error::Error{ "In " + v + ": operand isn't chrono literal." });
		}
	};

}/*namespace args_validator*/