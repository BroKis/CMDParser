#pragma once 
#include "abstract_arg.hpp"
#include "args_validator.hpp"
#include "utils.hpp"
#include "user_types.hpp"
namespace multi_arg
{
	/**
	*@brief Шаблон класса множественного аргумента
	* Содержит вектор шаблонных параметров
	*/
	template<typename T,typename K>
	class MultiArgument : public abstract_arg::AbstractArg
	{
	private:
		/// Поле содержащее вектор параметров
		std::vector<T> parameter{};
		/// Поле содержащее ссылку на шаблонный валидатор
		args_validator::Validator<K>* _validator{};
	public:
		MultiArgument(char shortName, std::string_view longName, bool requiredParameter) : AbstractArg(shortName, longName, requiredParameter) {};
		MultiArgument(std::string_view longName, bool requiredParameter) : AbstractArg(longName, requiredParameter) {};

		/// Геттер для размера вектора
		const size_t getSize() const {
			return parameter.size();
		}
		/// Геттер для элемента вектора
		/// @param[in] index входной аргумент
		const T& getByIndex(const size_t index)
		{
			return parameter[index];
		}

		args_error::ParseResult SetValue(const std::string& str) override 
		{
			T value;
			if (auto result = _validator->check(str); !result.isOk()) return result;
			if (const auto result = user_types::ParseUserType(value, str); !result.isOk()) return result;

			parameter.push_back(value);
			return args_error::ParseResult::Ok();
		}

		args_error::ParseResult SetValue() override
		{
			return args_error::ParseResult::Ok();
		}

		void setValidator(args_validator::Validator<K>* validator)
		{
			_validator = validator;
		}
	};

	/**
	*@brief Шаблон класса множественного целого аргумента
	* Содержит вектор целых параметров
	*/
	template<>
	class MultiArgument<int,int>:public abstract_arg::AbstractArg
	{
	private:
		/// Поле содержащее вектор целых параметров
		std::vector<int> parameter{};
		args_validator::Validator<int>* _validator{};
	public:
		MultiArgument(char shortName, std::string_view longName, bool requiredParameter) : AbstractArg(shortName, longName, requiredParameter) {};
		MultiArgument(std::string_view longName, bool requiredParameter) : AbstractArg(longName, requiredParameter) {};

		const size_t getSize() const {
			return parameter.size();
		}

		const int getByIndex(const size_t index)
		{
			return parameter[index];
		}

		args_error::ParseResult SetValue(const std::string& param) override
		{
			try
			{
				auto val = std::stoi(param);
				if (const auto result = _validator->check(val); result.isOk())
				{
					parameter.push_back(val);
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
			parameter.push_back(0);
			return args_error::ParseResult::Ok();
		}

		void setValidator(args_validator::Validator<int>* validator)
		{
			_validator = validator;
		}
	};

	/**
	*@brief Шаблон класса множественного булевого аргумента
	* Содержит вектор целых параметров
	*/
	template<>
	class MultiArgument<bool, std::string> :public abstract_arg::AbstractArg
	{
	private:
		/// Поле содержащее вектор булевых параметров
		std::vector<bool> parameter{};
		args_validator::Validator<std::string>* _validator{};
	public:
		MultiArgument(char shortName, std::string_view longName, bool requiredParameter) : AbstractArg(shortName, longName, requiredParameter) {};
		MultiArgument(std::string_view longName, bool requiredParameter) : AbstractArg(longName, requiredParameter) {};

		const size_t getSize() const {
			return parameter.size();
		}

		const bool getByIndex(const size_t index)
		{
			return parameter[index];
		}

		args_error::ParseResult SetValue(const std::string& param) override
		{
			if (const auto result = _validator->check(param); result.isOk())
			{
				parameter.push_back(utils::stringToBool(param));
				return result;
			}
			else { return result; }
		}

		args_error::ParseResult SetValue() override
		{
			parameter.push_back(true);
			return args_error::ParseResult::Ok();
		}

		void setValidator(args_validator::Validator<std::string>* validator)
		{
			_validator = validator;
		}
	};

	/**
	*@brief Шаблон класса множественного строкового аргумента
	* Содержит вектор строковых параметров
	*/
	template<>
	class MultiArgument<std::string, std::string> :public abstract_arg::AbstractArg
	{
	private:
		/// Поле содержащее вектор булевых параметров
		std::vector<std::string> parameter{};
		args_validator::Validator<std::string>* _validator{};
	public:
		MultiArgument(char shortName, std::string_view longName, bool requiredParameter) : AbstractArg(shortName, longName, requiredParameter) {};
		MultiArgument(std::string_view longName, bool requiredParameter) : AbstractArg(longName, requiredParameter) {};

		const size_t getSize() const {
			return parameter.size();
		}

		const std::string getByIndex(const size_t index)
		{
			return parameter[index];
		}

		args_error::ParseResult SetValue(const std::string& param) override
		{

			if (const auto result = _validator->check(param); result.isOk())
			{
				parameter.push_back(param);
				return result;
			}
			else { return result; }
		}

		args_error::ParseResult SetValue() override
		{
			parameter.push_back("");
			return args_error::ParseResult::Ok();
		}
		void setValidator(args_validator::Validator<std::string>* validator)
		{
			_validator = validator;
		}
	};

	/**
	*@brief Шаблон класса множественного вещественногог аргумента
	* Содержит вектор вещественных параметров
	*/
	template<>
	class MultiArgument<float, float> :public abstract_arg::AbstractArg
	{
	private:
		/// Поле содержащее вектор вещественных параметров
		std::vector<float> parameter;
		args_validator::Validator<float>* _validator{};
	public:
		MultiArgument(char shortName, std::string_view longName, bool requiredParameter) : AbstractArg(shortName, longName, requiredParameter) {};
		MultiArgument(std::string_view longName, bool requiredParameter) : AbstractArg(longName, requiredParameter) {};

		const size_t getSize() const {
			return parameter.size();
		}

		const float getByIndex(const size_t index)
		{
			return parameter[index];
		}

		args_error::ParseResult SetValue(const std::string& param) override
		{
			try
			{
				auto val = std::stof(param);
				if (const auto result = _validator->check(val); result.isOk())
				{
					parameter.push_back(val);
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
			parameter.push_back(0);
			return args_error::ParseResult::Ok();
		}
		void setValidator(args_validator::Validator<float>* validator)
		{
			_validator = validator;
		}
	};

	/**
	*@brief Шаблон класса множественного целого беззнакового аргумента
	* Содержит вектор целых беззнаковых параметров
	*/
	template<>
	class MultiArgument<unsigned int, unsigned int> :public abstract_arg::AbstractArg
	{
	private:
		/// Поле содержащее вектор вещественных параметров
		std::vector<unsigned int> parameter{};
		args_validator::Validator<unsigned int>* _validator{};
	public:
		MultiArgument(char shortName, std::string_view longName, bool requiredParameter) : AbstractArg(shortName, longName, requiredParameter) {};
		MultiArgument(std::string_view longName, bool requiredParameter) : AbstractArg(longName, requiredParameter) {};

		const size_t getSize() const {
			return parameter.size();
		}

		const float getByIndex(const size_t index)
		{
			return (float)parameter[index];
		}

		args_error::ParseResult SetValue(const std::string& param) override
		{
			try {
				unsigned int val = std::atoi(param.c_str());
				if (const auto result = _validator->check(val); result.isOk())
				{
					parameter.push_back(val);
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
			parameter.push_back(0);
			return args_error::ParseResult::Ok();
		}

		void setValidator(args_validator::Validator<unsigned int>* validator)
		{
			_validator = validator;
		}
	};
}/*namespace multi_arg*/