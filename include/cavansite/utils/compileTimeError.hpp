#pragma once

#include <cavansite/utils/StructuralString.hpp>


namespace cavansite::utils {

template <StructuralString S>
void compileTimeError() noexcept;

} // namespace cavansite::except