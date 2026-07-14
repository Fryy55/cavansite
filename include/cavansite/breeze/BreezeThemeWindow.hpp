#pragma once

#include <cavansite/breeze/impl/macro-check.hpp>

#include <QWidget>
#include <QBoxLayout>


namespace cavansite {

class BreezeThemeWindow final : public QWidget {
	Q_OBJECT

public:
	BreezeThemeWindow(QWidget* parent = nullptr);

private:
	[[nodiscard]] QHBoxLayout* createThemeToggleSettings() const;

	[[nodiscard]] QVBoxLayout* createThemeColorSettings() const;
	[[nodiscard]] QVBoxLayout* createThemeModeSettings() const;
	[[nodiscard]] QVBoxLayout* createThemeAltSettings() const;

public:
	BreezeThemeWindow(BreezeThemeWindow const&) = delete;
	BreezeThemeWindow& operator=(BreezeThemeWindow const&) = delete;
	BreezeThemeWindow(BreezeThemeWindow&&) = delete;
	BreezeThemeWindow& operator=(BreezeThemeWindow&&) = delete;
	
	~BreezeThemeWindow() noexcept override = default;

private:
	void keyPressEvent(QKeyEvent*) override;
};


} // namespace cavansite