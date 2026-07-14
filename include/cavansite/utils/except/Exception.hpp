#pragma once

#include <exception>
#include <string>


namespace cavansite {

namespace except {

class Exception : public std::exception {
public:
	constexpr Exception(std::string what) noexcept : m_what(std::move(what)) {}
	
	constexpr Exception(Exception const&) noexcept = default;
	constexpr Exception& operator=(Exception const&) noexcept = default;
	constexpr Exception(Exception&&) noexcept = default;
	constexpr Exception& operator=(Exception&&) noexcept = default;
	
	constexpr ~Exception() noexcept override = default;

public:
	[[nodiscard]] constexpr char const* what() const noexcept override {
	return m_what.c_str();
}

// Fields
protected:
	std::string m_what;
};

} // namespace except


namespace utils {

void handleException(std::exception const& exception) noexcept;

} // namespace utils

} // namespace cavansite