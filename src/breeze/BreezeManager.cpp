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
	static BreezeManager instance{};

	return &instance;
}

bool BreezeManager::isDestroyed() noexcept {
	return s_destroyed.load();
}

BreezeManager::BreezeManager() noexcept {
	QObject::connect(
		QGuiApplication::styleHints(), &QStyleHints::colorSchemeChanged,
		[this](Qt::ColorScheme mode) {
			this->setTheme(m_theme.inferRealMode(mode));
		}
	);

	try {
		this->setTheme(
			SettingsManager::get()->readForceDefault("breeze/theme").value
		);
		m_enabled = SettingsManager::get()->readForceDefault("breeze/enabled").value.toBool();
	} catch (std::exception const& e) {
		utils::handleException(e);
	}

	log::info("[cavansite] BreezeManager initialized");
}

BreezeManager::~BreezeManager() noexcept {
	log::info("[cavansite] BreezeManager destroyed");

	s_destroyed.store(true);
}


void BreezeManager::setTheme(BreezeTheme theme) {
	if (!m_enabled) {
		throw except::Exception{ "" };
	}

	m_theme = theme;

	QString themePrefix = theme.getPrefix();
	QString themeFile{ themePrefix % "/stylesheet.qss" };

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

	for (auto i : m_interfaces)
		i->themeUpdate(themePrefix, m_theme);

	return;
}

void BreezeManager::setEnabled(bool enabled) {
	m_enabled = enabled;

	if (m_enabled)

	return;
}


void BreezeManager::registerInterface(BreezeIconsInterface* widget) {
	if (!(m_interfaces.emplace(widget).second)) {
		log::error(
			"[cavansite] InterfaceException | Interface {} (RTTI: {}) is already registered",
			static_cast<void*>(widget), typeid(*widget).name()
		);

		throw except::InterfaceException("Interface already registered!");
	}

	log::debug(
		"[cavansite] Registered a widget at {} to BreezeManager",
		static_cast<void*>(widget)
	);

	return;
}

void BreezeManager::unregisterInterface(BreezeIconsInterface* widget) {
	if (!m_interfaces.erase(widget)) {
		log::error(
			"[cavansite] InterfaceException | Interface {} (RTTI: {}) isn't registered",
			static_cast<void*>(widget), typeid(*widget).name()
		);

		throw except::InterfaceException("Interface isn't registered!");
	}

	log::debug(
		"[cavansite] Unregistered a widget at {} from BreezeManager",
		static_cast<void*>(widget)
	);

	return;
}


#endif // CAVANSITE_ADD_BREEZE