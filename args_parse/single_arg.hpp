#pragma once
#include "abstract_arg.hpp"
#include "args_validator.hpp"
#include "utils.hpp"
#include "user_types.hpp"
namespace single_arg
{
	/**
	*@brief Шаблон класса одиночного аргумента
	* Содержит шаблонный параметр
	*/
	template<typename T,typename K = std::string>
	class SingleArgument : public abstract_arg::AbstractArg
	{
	private:
		/// Поле, хранящее значение аргумента если парсинг успешный
		T parameter{};
		/// Поле хранящее ссылку на валидатор для проверки значений
		args_validator::Validator<K>* _validator{};
	public:
		SingleArgument(char shortName, std::string_view longName, bool requiredParameter) : AbstractArg(shortName, longName, requiredParameter) {};
		SingleArgument(std::string_view longName, bool requiredParameter) : AbstractArg(longName, requiredParameter) {};

		args_error::ParseResult SetValue(const std::string& str) override
		{
			if (auto result = user_types::ParseUserType(parameter, str); !result.isOk()) return result;
			if (auto result = _validator->check(str); !result.isOk())return result;
			return args_error::ParseResult::Ok();
		}

		/// Сеттер для _validator
		void setValidator(args_validator::Validator<K>* validator)
		{
			_validator = validator;
		}

		/// Геттер для parameter
		const T& GetValue() const {
			return parameter;
		}

		args_error::ParseResult SetValue() override 
		{
			return args_error::ParseResult::Ok();
		}
	};

	/**
	* @brief Шаблонный класс целого аргумента
	* Содержит целый параметр
	*/
	template<> 
	class SingleArgument<int,int> : public abstract_arg::AbstractArg
	{
	private:
		/// Поле хранящее значение параметра аргумента
		int parameter = -1;
		/// Поле хранящее ссылку на валидатор для целых аргументов
		args_validator::Validator<int>* _validator{};
	public:
		SingleArgument(char shortName, std::string_view longName, bool requiredParameter) : AbstractArg(shortName, longName, requiredParameter) {};
		SingleArgument(std::string_view longName, bool requiredParameter) : AbstractArg(longName, requiredParameter) {};

		args_error::ParseResult SetValue(const std::string& param) override
		{
			try
			{
				auto val = std::stoi(param);
				if (const auto result = _validator->check(val); result.isOk())
				{
					parameter = val;
					return result;
				}
				else { return result; }
			}
			catch (...)
			{
				return  args_error::ParseResult::Fail({ "Incorrect argument:" + param + ".Error of conversation." });
			}
			
		}

		args_error::ParseResult SetValue() override
		{
			parameter = 0;
			return args_error::ParseResult::Ok();
		}

		const int GetValue() const {
			return parameter;
		}

		void setValidator(args_validator::Validator<int>* validator)
		{
			_validator = validator;
		}
	};

	/**
	* @brief Шаблонный класс булевого аргумента
	* Содержит булевый параметр
	*/
	template<>
	class SingleArgument<bool,std ::string> : public abstract_arg::AbstractArg
	{
	private:
		/// Поле хранящее значение параметра аргумента
		bool parameter = false;
		/// Поле хранящее ссылку на валидатор для булевых аргументов
		args_validator::Validator<std::string>* _validator{};
	public:
		SingleArgument(char shortName, std::string_view longName, bool requiredParameter) : AbstractArg(shortName, longName, requiredParameter) {};
		SingleArgument(std::string_view longName, bool requiredParameter) : AbstractArg(longName, requiredParameter) {};

		args_error::ParseResult SetValue(const std::string& param) override
		{
			if (const auto result = _validator->check(param); result.isOk())
			{
				parameter = utils::stringToBool(param);
				return result;
			}
			else { return result; }
		}

		args_error::ParseResult SetValue() override
		{
			parameter = true;
			return args_error::ParseResult::Ok();
		}
		const bool GetValue() const {
			return parameter;
		}

		void setValidator(args_validator::Validator<std::string>* validator)
		{
			_validator = validator;
		}
	};

	/**
	* @brief Шаблонный класс строкового аргумента
	* Содержит строковый параметр
	*/
	template<>
	class SingleArgument<std::string, std::string>:public abstract_arg::AbstractArg
	{
	private:
		/// Поле хранящее значение параметра аргумента
		std::string parameter = "";
		/// Поле хранящее ссылку на валидатор для строковых аргументов
		args_validator::Validator<std::string>* _validator{};
	public:
		SingleArgument(char shortName, std::string_view longName, bool requiredParameter) : AbstractArg(shortName, longName, requiredParameter) {};
		SingleArgument(std::string_view longName, bool requiredParameter) : AbstractArg(longName, requiredParameter) {};
		args_error::ParseResult SetValue(const std::string& param) override
		{
			if (const auto result = _validator->check(param); result.isOk())
			{
				parameter = param;
				return result;
			}
			else { return result; }
		}

		args_error::ParseResult SetValue() override
		{
			parameter = "defined";
			return args_error::ParseResult::Ok();
		}

		const std::string GetValue() const {
			return parameter;
		}

		void setValidator(args_validator::Validator < std::string > * validator)
		{
			_validator = validator;
		}
	};
	/**
	* @brief Шаблонный класс для вещественного аргумента
	* Содержит вещественный параметр
	*/
	template<>
	class SingleArgument<float, float>:public abstract_arg::AbstractArg
	{
	private:
		/// Поле хранящее значение параметра аргумента
		float parameter = 0;
		/// Поле хранящее ссылку на валидатор для вещественных аргументов
		args_validator::Validator<float>* _validator{};
	public:
		SingleArgument(char shortName, std::string_view longName, bool requiredParameter) : AbstractArg(shortName, longName, requiredParameter) {};
		SingleArgument(std::string_view longName, bool requiredParameter) : AbstractArg(longName, requiredParameter) {};
		args_error::ParseResult SetValue(const std::string& param) override
		{
			try
			{
				auto val = std::stof(param);
				if (const auto result = _validator->check(val); result.isOk())
				{
					parameter = val;
					return result;
				}
				else { return result; }
			}
			catch (...)
			{
				return args_error::ParseResult::Fail({ "Incorrect argument:" + param + ".Error of conversation. Check the input." });
			}
		
		}

		args_error::ParseResult SetValue() override
		{
			parameter = 0;
			return args_error::ParseResult::Ok();
		}
		const float GetValue() const {
			return parameter;
		}


		void setValidator(args_validator::Validator <float>* validator)
		{
			_validator = validator;
		}
	};

	/**
	* @brief Шаблонный класс для целого беззнакового аргумента
	* Содержит целый беззнаковый параметр
	*/
	template<>
	class SingleArgument<unsigned int, unsigned int>:public abstract_arg::AbstractArg
	{
	private:
		/// Поле хранящее значение параметра аргумента
		unsigned int parameter = 0;
		/// Поле хранящее ссылку на валидатор для вещественных аргументов
		args_validator::Validator<unsigned int>* _validator{};
	public:

		SingleArgument(char shortName, std::string_view longName, bool requiredParameter) : AbstractArg(shortName, longName, requiredParameter) {};
		SingleArgument(std::string_view longName, bool requiredParameter) : AbstractArg(longName, requiredParameter) {};
		args_error::ParseResult SetValue(const std::string& param) override
		{
			try
			{
				auto val = std::atoi(param.c_str());
				if (const auto result = _validator->check(val); result.isOk())
				{
					parameter = val;
					return result;
				}
				else { return result; }
			}
			catch (...)
			{
				return args_error::ParseResult::Fail({ "Incorrect argument:" + param + ".Error of conversation. Check the input." });
			}
			
		}

		args_error::ParseResult SetValue() override
		{
			parameter = 0;
			return args_error::ParseResult::Ok();
		}
		const unsigned int GetValue() const {
			return parameter;
		}

		void setValidator(args_validator::Validator<unsigned int>* validator)
		{
			_validator = validator;
		}
	};


}/*namespace single_arg*/