#pragma once

#include <cavansite/breeze/impl/macro-check.hpp>

#include <cavansite/breeze/BreezeTheme.hpp>


namespace cavansite {

class BreezeIconsInterface {
public:
	virtual ~BreezeIconsInterface() noexcept;

protected:
	std::pair<QString, BreezeTheme> registerBreezeInterface();

public:
	virtual void themeUpdate(QString const& prefix, BreezeTheme const& theme) = 0;
};

} // namespace cavansite