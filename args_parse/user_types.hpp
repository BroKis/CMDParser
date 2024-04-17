#pragma once
#include "args_error.hpp"
#include "args_validator.hpp"
#include "utils.hpp"
#include <chrono>
#include <regex>
#include <sstream>
namespace user_types
{
	/**
	*@brief Пользовательский тип времени
	* Хранит значение времени в микросекундах
	*/
	class ChronoCloack {
	private:
		std::chrono::microseconds _ms;
	public:
		ChronoCloack() = default;
		ChronoCloack(std::chrono::microseconds ms) : _ms{ ms } {}
		std::chrono::microseconds GetMicroseconds() const { return _ms; }
	};

	
	/**
	*@brief Шаблонный метод парсинга параметра пользовательского типа
	* Выполняет парсинг пришедшего параметра
	* @param[in] userType ссылка на объект
	* @param[in] parameter строка параметра для парсинга
	*/
	
	 args_error::ParseResult ParseUserType(ChronoCloack& userType, const std::string& parameter)
	{

		std::stringstream ss{ parameter };

		long long value;
		std::string unit;

		ss >> value >> unit;

		std::chrono::microseconds us;

		us = utils::chronoToMicroseconds(value, unit);

		userType = ChronoCloack{ us };

		return args_error::ParseResult::Ok();
	}
}/*namespace user_types*/
