#pragma once

#include <cavansite/utils/concepts.hpp>

#include <QGuiApplication>
#include <QStyleHints>

#include <functional>


#define CAVANSITE_GLOBAL_THEME_PARAM Qt::ColorScheme mode = QGuiApplication::styleHints()->colorScheme()

namespace cavansite::utils {

using GlobalThemeCallback = std::move_only_function<void(Qt::ColorScheme mode)>;

inline void listenForGlobalTheme(GlobalThemeCallback&& callback) noexcept {
	QObject::connect(
		QGuiApplication::styleHints(), &QStyleHints::colorSchemeChanged,
		std::move(callback)
	);
}

template <concepts::Class T>
void listenForGlobalTheme(T* instance, void (T::*memberFunction)(Qt::ColorScheme mode)) noexcept {
	listenForGlobalTheme(std::bind_front(memberFunction, instance));

	return;
}

} // namespace cavansite::utils