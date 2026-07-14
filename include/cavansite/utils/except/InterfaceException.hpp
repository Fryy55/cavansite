#pragma once

#include "Exception.hpp"


namespace cavansite::except {

class InterfaceException final : public Exception {
public:
	using Exception::Exception;
};

} // namespace cavansite::except