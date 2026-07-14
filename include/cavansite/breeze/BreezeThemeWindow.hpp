#pragma once

#include <cavansite/breeze/_internal/macro-check.hpp>

#include <cavansite/breeze/BreezeIconsInterface.hpp>
#include <cavansite/utils/compileTimeError.hpp>
#include <cavansite/classes/Separator.hpp>

#include <QWidget>
#include <QGroupBox>
#include <QBoxLayout>
#include <QRadioButton>
#include <QPushButton>


namespace cavansite {

class BreezeThemeWindow final : public QWidget, public BreezeIconsInterface {
	#ifdef CAVANSITE_ADD_BREEZE
		Q_OBJECT
	#endif

public:
	BreezeThemeWindow(QWidget* parent = nullptr);

private:
	[[nodiscard]] QGroupBox* createThemeColorSettings(BreezeTheme const&);
	[[nodiscard]] QGroupBox* createThemeModeSettings(BreezeTheme const&);
	[[nodiscard]] QVBoxLayout* createThemeAltSettings() const;

	[[nodiscard]] static consteval BreezeTheme::Color colorForTheme(std::string_view theme) {
		if (theme == "red") {
			return BreezeTheme::Color::Red;
		} else if (theme == "orange") {
			return BreezeTheme::Color::Orange;
		} else if (theme == "yellow") {
			return BreezeTheme::Color::Yellow;
		} else if (theme == "green") {
			return BreezeTheme::Color::Green;
		} else if (theme == "cyan") {
			return BreezeTheme::Color::Cyan;
		} else if (theme == "blue") {
			return BreezeTheme::Color::Blue;
		} else if (theme == "purple") {
			return BreezeTheme::Color::Purple;
		} else if (theme == "pink") {
			return BreezeTheme::Color::Pink;
		} else if (theme == "mono") {
			return BreezeTheme::Color::Monochrome;
		} else {
			utils::compileTimeError<"Unknown Breeze theme color">();

			return BreezeTheme::Color::Red;
		}
	}

public:
	BreezeThemeWindow(BreezeThemeWindow const&) = delete;
	BreezeThemeWindow& operator=(BreezeThemeWindow const&) = delete;
	BreezeThemeWindow(BreezeThemeWindow&&) = delete;
	BreezeThemeWindow& operator=(BreezeThemeWindow&&) = delete;

	~BreezeThemeWindow() noexcept override = default;

private:
	void keyPressEvent(QKeyEvent*) override;
	void themeUpdate(QString const&, BreezeTheme) override;

private: // Fields
	#ifdef CAVANSITE_BREEZE_THEME_MONO
		QPushButton* m_monoButton;
	#endif
	QRadioButton* m_light;
	QRadioButton* m_dark;
	QRadioButton* m_system;
	Separator* m_separator;

	std::array<QPushButton*, CAVANSITE_ADD_BREEZE> m_buttons;
};


} // namespace cavansite