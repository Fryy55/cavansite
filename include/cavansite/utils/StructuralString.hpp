#pragma once

#include <array>
#include <algorithm>
#include <string_view>


namespace cavansite::utils {

template <std::size_t N>
struct StructuralString final {
	consteval StructuralString(char const (& string)[N]) noexcept { // NOLINT(modernize-avoid-c-arrays)
		std::copy_n(string, N, data.begin());
	}

	[[nodiscard]] consteval std::string_view string() const noexcept { return { data.data(), data.size() - 1z }; }

	std::array<char, N> data;
};

} // namespace cavansite::utils