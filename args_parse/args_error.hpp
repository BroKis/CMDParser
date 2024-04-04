#pragma once
#include <string>
#include <optional>
namespace args_error
{
	struct Error {
		std::string description;
	};

	class [[nodiscard]] ParseResult {
		std::optional<Error> error;

		ParseResult() = default;
		ParseResult(Error error) : error{ std::move(error) } {};

	public:
		static ParseResult Ok() { return ParseResult{}; };
		static ParseResult Fail(Error error) { return ParseResult{ std::move(error) }; };

		[[nodiscard]]bool isOk() const { return !this->error.has_value(); };

		[[nodiscard]] const Error& Error() const { return this->error.value(); };
	};
}