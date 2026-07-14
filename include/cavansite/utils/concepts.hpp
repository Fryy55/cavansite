#pragma once

#include <type_traits>


namespace cavansite::concepts {

template <typename T>
concept Class = std::is_class_v<T> || std::is_union_v<T>;

} // namespace cavansite::concepts