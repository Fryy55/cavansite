#ifdef CAVANSITE_ADD_BREEZE


#include <cavansite/breeze/BreezeManager.hpp>

#include <cavansite/classes/singletons/SettingsManager.hpp>
#include <cavansite/breeze/BreezeIconsInterface.hpp>

#include <QFile>
#include <QApplication>

#include <aurora/log.hpp>

using namespace aurora;
using namespace cavansite;


BreezeManager* BreezeManager::get() noexcept {
	static auto instance = new BreezeManager; // NOLINT(bugprone-unhandled-exception-at-new)

	return instance;
}

BreezeManager::BreezeManager() noexcept {
	utils::listenForGlobalTheme([this](Qt::ColorScheme mode) {
		this->setTheme(m_theme.inferRealMode(mode));
	});

	try {
		m_enabled = SettingsManager::get()->readForceDefault("breeze/enabled").value.toBool();
		this->setTheme(
			SettingsManager::get()->readForceDefault("breeze/theme").value
		);
	} catch (std::exception const& e) {
		utils::handleException(e);
	}

	log::info("[cavansite] BreezeManager initialized");
}


BreezeTheme BreezeManager::getTheme() const noexcept {
	if (m_enabled)
		return m_theme;
	else
		return BreezeTheme{ BreezeTheme::Color::Monochrome, BreezeTheme::Mode::System, false };
}

void BreezeManager::setTheme(BreezeTheme theme, bool writeToSettings) {
	using namespace Qt::StringLiterals;

	#ifndef CAVANSITE_BREEZE_THEME_MONO
		if (!m_enabled) {
			log::warn("[cavansite] Theme failsafe activated. Breeze themes seem to be disabled with no monochrome theme added; forcibly enabling Breeze themes");

			m_enabled = true;
			SettingsManager::get()->writeForceDefault("breeze/enabled", true);
		}
	#endif

	m_theme = theme;

	if (!m_enabled)
		theme = this->getTheme();

	QString themePrefix = theme.getPrefix();

	if (m_enabled) {
		QString themeFile{ themePrefix % u"/stylesheet.qss"_s };

		QFile file{ themeFile };
		if (!file.open(QFile::ReadOnly | QFile::Text)) {
			log::warn("[cavansite] Couldn't read '{}'", themeFile.toStdString());

			return;
		}

		qApp->setStyleSheet(file.readAll());
		log::info(
			"[cavansite] Theme set to '{}'. Sending theme update to {} interfaces",
			theme.getPrefix().slice(2z).toStdString(), m_interfaces.size()
		);
	} else {
		qApp->setStyleSheet("");
		log::info(
			"[cavansite] Breeze themes disabled. Sending 'mono' theme update to {} interfaces",
			m_interfaces.size()
		);
	}

	for (auto i : m_interfaces)
		i->themeUpdate(themePrefix, theme);

	if (writeToSettings)
		SettingsManager::get()->writeForceDefault("breeze/theme", theme);

	return;
}

void BreezeManager::setEnabled(bool enabled, bool writeToSettings) {
	m_enabled = enabled;

	this->setTheme(m_theme);

	if (writeToSettings)
		SettingsManager::get()->writeForceDefault("breeze/enabled", m_enabled);

	return;
}


void BreezeManager::registerInterface(BreezeIconsInterface* widget) {
	if (!(m_interfaces.emplace(widget).second)) {
		throw except::InterfaceException{ std::format(
			"Interface {} (RTTI: {}) is already registered!",
			static_cast<void*>(widget), typeid(*widget).name()
		) };
	}

	log::debug(
		"[cavansite] Registered a widget at {} to BreezeManager",
		static_cast<void*>(widget)
	);

	return;
}

void BreezeManager::unregisterInterface(BreezeIconsInterface* widget) {
	if (!m_interfaces.erase(widget)) {
		throw except::InterfaceException{ std::format(
			"Interface {} (RTTI: {}) isn't registered!",
			static_cast<void*>(widget), typeid(*widget).name()
		) };
	}

	log::debug(
		"[cavansite] Unregistered a widget at {} from BreezeManager",
		static_cast<void*>(widget)
	);

	return;
}


#endif // CAVANSITE_ADD_BREEZE