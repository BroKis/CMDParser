#pragma once
#include <string>
#include <optional>
namespace args_error
{
	/**
	* @brief Структура для создания ошибки
	*/
	struct Error {
		std::string description;//<поле для описания ошибки
	};

	/**
	* @brief Класс для реализации выбрасывания ошибок
	* Данный класс реализует методы для реализации механизма ошибок
	*/
	class [[nodiscard]] ParseResult {
		std::optional<Error> error;///<Поле содержащее структуру @Error

		ParseResult() = default; ///<Конструктор по умолчанию
		ParseResult(Error error) : error{ std::move(error) } {}; ///<Конструктор, если есть ошибка

	public:
		/**
		*@brief Метод который возвращает конструктор по умолчанию, если нет ошибок
		*/
		static ParseResult Ok() { return ParseResult{}; };
		/**
		*@brief Метод который возвращает конструктор с ошибкой, если ошибка есть
		*/
		static ParseResult Fail(
			Error error///<Поле для описания ошибки
		) {
			return ParseResult{ std::move(error) };
		};

		/**
		*@brief Метод который возвращает истинное значение, если ошибки нет
		*/
		[[nodiscard]] bool isOk() const { return !this->error.has_value(); };


		/**
		*@brief Метод который возвращает ложное значение, если ошибка есть
		*/
		[[nodiscard]] const Error& Error() const { return this->error.value(); };
	};
}/*namespace args_error*/