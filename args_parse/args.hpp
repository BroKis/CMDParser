#pragma once
#include "abstract_arg.hpp"
#include "args_validator.hpp"
#include "utils.hpp"
#include <iostream>
#include <algorithm>
#include <string>
namespace args_parser
{
	std::string extractable = "=";

	/**@brief Функция для обработки аргументов командной строки.
	*@param[in] argc количество аргументов командной строки
	*@param[in] argv поток аргументов командной строки
	*/
	void EatParams(
		int argc,
		const char** argv)
	{
		for (int i = 0; i < argc; ++i)
		{
			std::cout << "[" << i << "]: '" << argv[i] << "'" << std::endl;
		}
	}
	/**
	*@brief Парсер аргументов командной строки
	*/
	template<typename T = std::string>
	class ArgsParser
	{

	public:
		/**@brief Метод, добавляющий аргумент в вектор аргументов
		*@param[in] arg указатель на базовый класс  
		*/
		virtual void add(
			abstract_arg::AbstractArg* arg
		) {
			Args.push_back(arg);
		}

		/**@brief Метод, который парсит входной поток аргументов*/
		virtual args_error::ParseResult parse(
			/// сколько всего аргументов
			int argc,
			/// значений аргументов. Должно быть ровно @argc
			const char** argv)
		{
			for (int i = 1; i < argc; i++)
			{
				std::string temp_arg = argv[i];
				if (const auto result = tryParse(temp_arg); result.isOk())
				{
					if (temp_arg.find("--") == 0)
					{
						if (const auto result = parseLongCommandArgument(temp_arg, argv, i); !result.isOk()) return result;
					}
					else if (temp_arg.find("-") == 0)
					{
						if (const auto result = parseShortCommandArgument(temp_arg, argv, i); !result.isOk())return result;
					}
				}
				else
				{
					return result;
				}
			}
			return args_error::ParseResult::Ok();
		}
		
		/**@brief Метод для извлечения аргумента из вектора аргуменета*/
		virtual abstract_arg::AbstractArg* getArgumentFromVector(
			///номер аргумента в векторе
			int index
		) const
		{
			if (index < Args.size())
			{
				return Args[index];
			}
			return nullptr;
		}

		/** @brief Метод, устанавливающий валидатор парсера командной строки*/
		void SetValidator(
			/// валидатор парсера командной строки
			args_validator::Validator<T>* validator
		)
		{
			_validator = validator;
		}
		/**@brief Метод выводящий информацию об аргументах*/
		virtual std::string GetHelp() const
		{
			std::string result = "";

			for (const auto& arg : Args) {
				result += "-";
				result += arg->getShortName();
				result += " --";
				result += arg->getLongName();
				result += " | ";
				result += arg->getDescription();
			}
			return result;
		}
	private:
		/**@brief Метод, который проверяет можно ли распарсить аргумент*/
		virtual args_error::ParseResult tryParse(
			/// Аргумент, который нужнот распарсить
			const std::string& parseable_arg
		)
		{
			return _validator->check(parseable_arg);
		}

		/** @brief Метод, который выделяет параметр из аргумента */
		virtual std::string extractParameter(
			/// строка-источник
			const std::string& source,
			/// разделитель
			std::string& extractable)
		{
			auto it = std::search(source.begin(), source.end(),
				extractable.begin(), extractable.end());
			std::string argument(it + 1, source.end());
			return argument;
		}

		/** @brief Метод, устанавливающий значение для длинной команды со знаком = или без*/
		virtual args_error::ParseResult setParamsInLongNameWithEqualOrWithout(
			/// строка источник
			const std::string& source,
			/// аргумент которому присваивается значение
			abstract_arg::AbstractArg* arg,
			/// масств аргументов
			const char** argv,
			/// индекс аргумента командной строки
			int& index
		) 
		{
			if (source.find('=') == std::string::npos) return arg->SetValue(argv[++index]);
			return arg->SetValue(extractParameter(source, extractable));
		}

		/** @brief Метод, устанавливающий значение для коротокй команды со знаком =*/
		
		virtual args_error::ParseResult setParamsInShortNameWithEqual(
			/// строка-источник
			const std::string& source,
			/// аргумент, которому устанавливается значение
			abstract_arg::AbstractArg* arg
		)
		{
			if (!arg->isParamRequired())
				return args_error::ParseResult::Fail(args_error::Error{ "The argument to which you are trying to assign the parameter is empty" });
			return arg->SetValue(extractParameter(source, extractable));
		}

		/** @brief Метод, устанавливающий значение для коротокй команды без знака =*/
		virtual args_error::ParseResult setParamsInShortNameWithoutEqual(
			/// строка-источник
			const std::string& source,
			/// аргумент, которому присваивают значение
			abstract_arg::AbstractArg* arg,
			/// массив аргументов
			const char** argv,
			/// индекс аргумента
			int& index)
		{
			if (source.find(arg->getShortName()) == source.size() - 1 && arg->isParamRequired())
			{
				return arg->SetValue(argv[++index]);
			}
			if (!arg->isParamRequired())
			{
				return arg->SetValue();
			}
			std::string delimeter(1, arg->getShortName());
			return arg->SetValue(extractParameter(source, delimeter));
		}

		/** @brief Метод, парсящий длинную команду*/
		virtual args_error::ParseResult parseLongCommandArgument(
			/// строка-источник
			const std::string& source,
			/// массив аргументов
			const char** argv,
			/// индекс аргумента
			int& index)
		{
			for (const auto& arg : Args)
			{
				std::string findArgument = utils::extractShortFormOfLongName(source);
				if (arg->getLongName() == findArgument || (arg->getLongName().find(findArgument) != std::string::npos && !arg->isDefined()))
				{
					if (const auto result = setParamsInLongNameWithEqualOrWithout(source, arg, argv, index); !result.isOk()) return result;
					if (!arg->isDefined()) arg->setDefinded(true);
				}
			}
			return args_error::ParseResult::Ok();
		}

		/** @brief Метод, парсящий короткую команду */
		virtual args_error::ParseResult parseShortCommandArgument(
			/// короткая команда
			const std::string& source,
			/// массив аргументов
			const char** argv,
			/// индекс аргумента
			int& index
		)
		{
			for (const auto& arg : Args)
			{
				if (source.find(arg->getShortName()) != std::string::npos)
				{
					if (source.find('=') != std::string::npos)
					{
						if (const auto result = setParamsInShortNameWithEqual(source, arg); !result.isOk()) return result;
					}
					else
					{
						if (const auto result = setParamsInShortNameWithoutEqual(source, arg, argv, index);  !result.isOk()) return result;
					}
					if (!arg->isDefined()) arg->setDefinded(true);
				}
			}
			return args_error::ParseResult::Ok();
		}



		/// Поле хранящее ссылку для валидатора парсера
		args_validator::Validator<T>* _validator{};
		/// Поле хрянящее список аргументов
		std::vector<abstract_arg::AbstractArg*> Args{};
	};
}