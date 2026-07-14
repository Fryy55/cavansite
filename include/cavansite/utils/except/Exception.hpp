#pragma once

#include <cavansite/utils/StructuralString.hpp>

#include <aurora/log.hpp>

#include <exception>
#include <string>
#include <functional>


namespace cavansite {

namespace except {

class ExceptionType {
public:
	[[nodiscard]] virtual char const* what() const noexcept = 0;
	[[nodiscard]] virtual constexpr std::string_view className() const noexcept = 0;
};

namespace _internal {

template <utils::StructuralString ClassName>
class ExceptionBase final : public std::exception, public ExceptionType {
public:
	ExceptionBase(std::string what) noexcept : m_what{ std::move(what) } {
		aurora::log::error(
			"[cavansite] {} | {}",
			this->className(), m_what
		);
	}
	
	ExceptionBase(ExceptionBase const&) noexcept = default;
	ExceptionBase& operator=(ExceptionBase const&) noexcept = default;
	ExceptionBase(ExceptionBase&&) noexcept = default;
	ExceptionBase& operator=(ExceptionBase&&) noexcept = default;

	~ExceptionBase() noexcept override = default;

public:
	[[nodiscard]] char const* what() const noexcept override { return m_what.c_str(); }
	[[nodiscard]] constexpr std::string_view className() const noexcept override { return ClassName.string(); }

private: // Fields
	std::string m_what;
};

} // namespace _internal

#define CAVANSITE_REGISTER_EXCEPTION(name) using name = ::cavansite::except::_internal::ExceptionBase<#name> // NOLINT(bugprone-macro-parentheses)

CAVANSITE_REGISTER_EXCEPTION(Exception);

} // namespace except


namespace utils {

void handleException(std::exception const& exception) noexcept;

using ExceptionHandler = std::move_only_function<void(std::exception const&) noexcept>;
void setExceptionHandler(ExceptionHandler&& handler) noexcept;

} // namespace utils

} // namespace cavansite