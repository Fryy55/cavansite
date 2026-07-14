#pragma once

#include <cavansite/breeze/_internal/macro-check.hpp>

#include <cavansite/breeze/BreezeTheme.hpp>


namespace cavansite {

class BreezeIconsInterface {
public:
	virtual ~BreezeIconsInterface() noexcept;

protected:
	[[nodiscard("You might want to use the provided prefix and theme to configure your widgets")]]
	std::pair<QString, BreezeTheme> registerBreezeInterface();

public:
	virtual void themeUpdate(QString const& prefix, BreezeTheme theme) = 0;
};

} // namespace cavansite