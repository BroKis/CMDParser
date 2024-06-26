#pragma once
#include <string>
#include <vector>
#include "args_error.hpp"
namespace abstract_arg
{
	/**
	*@brief Базовый абстрактный класс
	* частично реализует общий функционал всех классов
	*/
	class AbstractArg
	{
	private:
		/// Указывает определен ли аргумент
		bool isDefine = false;
		/// Указывает длинное имя аргумента
		std::string longName{};
		/// Указывает короткое имя аргумента
		char shortName{};
		/// Указывает описание аргумента
		std::string description{};
		/// Указывает требуется ли параметр
		bool requiredParameter = false;
	public:
		AbstractArg(char shortName, std::string_view longName, bool requiredParameter) : shortName(shortName), longName(longName), requiredParameter(requiredParameter) {};
		AbstractArg(std::string_view longName, bool requiredParameter): longName(longName), requiredParameter(requiredParameter) {};
		virtual ~AbstractArg() = default;
		/// Геттер для shortName
		char getShortName() const
		{
			return shortName;
		}
		/// Геттер для longName
		std::string getLongName() const
		{
			return longName;
		}
		/// Сеттер для description
		virtual void addDescription(const std::string& desc) {
			description = desc;
		}
		/// Геттер для description
		std::string_view getDescription() const 
		{
			return description;
		};
		/// Геттер для isDefine
		[[nodiscard]]bool isDefined() const
		{
			return isDefine;
		}
		/// Сеттер для isDefine
		void setDefinded(bool flag) {
			isDefine = flag;
		}
		/// Геттер для requiredParameter
		[[nodiscard]]bool isParamRequired() const {
			return requiredParameter;
		}
		/**
		*@brief Метод присваивания параметра аргументу, если требуется параметр
		* Выполняет присваивание параметра аргументу
		* @param[in] param входной аргумент
		*/
		[[nodiscard]]virtual args_error::ParseResult SetValue(const std::string& param) =0;
		/**
		*@brief Метод присваивания параметра аргументу, если не требуется параметр
		* Выполняет присваивание параметра аргументу
		*/
		[[nodiscard]]virtual args_error::ParseResult SetValue() = 0;
	};


}/*namespace abstract_arg*/