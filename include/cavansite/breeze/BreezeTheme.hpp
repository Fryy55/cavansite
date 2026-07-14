#pragma once

#include <cavansite/breeze/impl/macro-check.hpp>

#include <cavansite/utils/except/Exception.hpp>

#include <QGuiApplication>
#include <QStyleHints>
#include <QColor>

#include <aurora/log.hpp>

#include <cstdint>


namespace cavansite {

class BreezeTheme final {
	friend class BreezeManager;

public:
	enum class Color : std::uint8_t {
		Red,
		Orange,
		Yellow,
		Green,
		Cyan,
		Blue,
		Purple,
		Pink,
		Monochrome
	};

	enum class Mode : std::uint8_t {
		Dark,
		Light,
		System
	};

public:
	constexpr BreezeTheme() noexcept : m_providedMode(Mode::System), m_alt(false) {
		m_color =
			#ifdef CAVANSITE_BREEZE_THEME_BLUE
				Color::Blue;
			#elifdef CAVANSITE_BREEZE_THEME_RED
				Color::Red;
			#elifdef CAVANSITE_BREEZE_THEME_ORANGE
				Color::Orange;
			#elifdef CAVANSITE_BREEZE_THEME_YELLOW
				Color::Yellow;
			#elifdef CAVANSITE_BREEZE_THEME_GREEN
				Color::Green;
			#elifdef CAVANSITE_BREEZE_THEME_CYAN
				Color::Cyan;
			#elifdef CAVANSITE_BREEZE_THEME_PURPLE
				Color::Purple;
			#elifdef CAVANSITE_BREEZE_THEME_PINK
				Color::Pink;
			#elifdef CAVANSITE_BREEZE_THEME_MONO
				Color::Monochrome;
			#endif

		this->inferRealMode();
	}
	constexpr BreezeTheme(
		Color color, Mode providedMode, bool alt
	) noexcept : m_color(color), m_providedMode(providedMode), m_alt(alt) {
		this->inferRealMode();
	}
	constexpr BreezeTheme(
		QVariant const& setting
	) {
		auto list = setting.toString().split('|');

		m_color = static_cast<Color>(list.at(0z).toUInt());
		m_providedMode = static_cast<Mode>(list.at(1z).toUInt());
		m_alt = list.at(2z).toUInt();
	}

private:
	constexpr BreezeTheme& inferRealMode(
		Qt::ColorScheme mode = QGuiApplication::styleHints()->colorScheme()
	) noexcept {
		switch (m_providedMode) {
			case Mode::System:
				m_realMode = mode == Qt::ColorScheme::Dark ? 
										Mode::Dark
										:
										Mode::Light;
				break;

			default:
				m_realMode = m_providedMode;
				break;
		}

		return *this;
	}

public:
	constexpr BreezeTheme(BreezeTheme const&) noexcept = default;
	constexpr BreezeTheme& operator=(BreezeTheme const&) noexcept = default;
	constexpr BreezeTheme(BreezeTheme&&) noexcept = default;
	constexpr BreezeTheme& operator=(BreezeTheme&&) noexcept = default;

	constexpr ~BreezeTheme() noexcept = default;

	inline operator QVariant() noexcept {
		return {
			QString::number(std::to_underlying(m_color))
			% "|" %
			QString::number(std::to_underlying(m_providedMode))
			% "|" %
			QString::number(m_alt)
		};
	}

public:
	[[nodiscard]] inline QString getPrefix() const {
		#define CAVANSITE_PREFIX_RET(color) \
			return { \
				QString{ ":/" } \
				% \
				QString{ m_realMode == Mode::Dark ? "dark-" : "light-" } \
				% \
				QString{ color } \
				% \
				QString{ m_alt ? "-alt" : "" } \
			}

		switch (m_color) {
			#ifdef CAVANSITE_BREEZE_THEME_RED
				case Color::Red:
					CAVANSITE_PREFIX_RET("red");
			#endif

			#ifdef CAVANSITE_BREEZE_THEME_ORANGE
				case Color::Orange:
					CAVANSITE_PREFIX_RET("orange");
			#endif

			#ifdef CAVANSITE_BREEZE_THEME_YELLOW
				case Color::Yellow:
					CAVANSITE_PREFIX_RET("yellow");
			#endif

			#ifdef CAVANSITE_BREEZE_THEME_GREEN
				case Color::Green:
					CAVANSITE_PREFIX_RET("green");
			#endif

			#ifdef CAVANSITE_BREEZE_THEME_CYAN
				case Color::Cyan:
					CAVANSITE_PREFIX_RET("cyan");
			#endif

			#ifdef CAVANSITE_BREEZE_THEME_BLUE
				case Color::Blue:
					CAVANSITE_PREFIX_RET("blue");
			#endif

			#ifdef CAVANSITE_BREEZE_THEME_PURPLE
				case Color::Purple:
					CAVANSITE_PREFIX_RET("purple");
			#endif

			#ifdef CAVANSITE_BREEZE_THEME_PINK
				case Color::Pink:
					CAVANSITE_PREFIX_RET("pink");
			#endif

			#ifdef CAVANSITE_BREEZE_THEME_MONO
				case Color::Monochrome:
					CAVANSITE_PREFIX_RET("mono");
			#endif

			default:
				aurora::log::error(
					"[cavansite] Exception | Unhandled Breeze theme color"
				);

				throw except::Exception{ "Unhandled Breeze theme color!" };
		}

		#undef CAVANSITE_PREFIX_RET
	}

	[[nodiscard]] inline QColor getAccentColor() const {
		switch (m_color) {
			#ifdef CAVANSITE_BREEZE_THEME_RED
				case Color::Red:
					return { 184, 50, 50 };
			#endif

			#ifdef CAVANSITE_BREEZE_THEME_ORANGE
				case Color::Orange:
					return { 233, 124, 60 };
			#endif

			#ifdef CAVANSITE_BREEZE_THEME_YELLOW
				case Color::Yellow:
					return { 255, 255, 0 };
			#endif

			#ifdef CAVANSITE_BREEZE_THEME_GREEN
				case Color::Green:
					return { 51, 184, 51 };
			#endif

			#ifdef CAVANSITE_BREEZE_THEME_CYAN
				case Color::Cyan:
					return { 50, 184, 184 };
			#endif

			#ifdef CAVANSITE_BREEZE_THEME_BLUE
				case Color::Blue:
					return { 61, 174, 233 };
			#endif

			#ifdef CAVANSITE_BREEZE_THEME_PURPLE
				case Color::Purple:
					return { 167, 75, 184 };
			#endif

			#ifdef CAVANSITE_BREEZE_THEME_PINK
				case Color::Pink:
					return { 230, 57, 186 };
			#endif

			#ifdef CAVANSITE_BREEZE_THEME_MONO
				case Color::Monochrome:
					return m_realMode == Mode::Dark ? QColor{ 255, 255, 255 } : QColor{ 28, 28, 28 };
			#endif

			default:
				aurora::log::error(
					"[cavansite] Exception | Unhandled Breeze theme color"
				);

				throw except::Exception{ "Unhandled Breeze theme color!" };
		}
	}

// Fields
public:
	Color m_color;
	Mode m_providedMode;
	Mode m_realMode;
	bool m_alt;
};

static_assert(
	std::is_trivially_copyable_v<BreezeTheme> && sizeof(BreezeTheme) <= sizeof(void*),
	"BreezeTheme isn't trivially copyable/bigger than a pointer; passing by value pessimizes optimization"
);

} // namespace cavansite