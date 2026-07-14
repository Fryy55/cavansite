#pragma once

#include "Exception.hpp"


namespace cavansite::except {

class SettingsException final : public Exception {
public:
	using Exception::Exception;
};

} // namespace cavansite::except