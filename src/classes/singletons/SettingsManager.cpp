#include <cavansite/classes/singletons/SettingsManager.hpp>

#include <cavansite/utils/except/SettingsException.hpp>

#include <aurora/log.hpp>

using namespace aurora;
using namespace cavansite;


SettingsManager* SettingsManager::get() {
	if (!s_instance) {
		log::error("[cavansite] SettingsException | SettingsManager hasn't been initialized");

		throw except::SettingsException{ "SettingsManager hasn't been initialized!" };
	}

	return s_instance.get();
}

bool SettingsManager::init(
	QString const& directoryName, QString const& filename,
	QSettings::Format format, QSettings::Scope scope
) noexcept {
	if (s_instance) {
		log::warn("[cavansite] SettingsManager has already been initialized!");

		return false;
	}

	s_instance.reset(new (std::nothrow) SettingsManager(directoryName, filename, format, scope));
	if (!s_instance) {
		log::error("[cavansite] Failed to initialize SettingsManager");

		return false;
	}

	return true;
}

void SettingsManager::Delete::operator()(SettingsManager* ptr) const noexcept {
		delete ptr;

		return;
}

SettingsManager::SettingsManager(
	QString const& directoryName, QString const& filename,
	QSettings::Format format, QSettings::Scope scope
) noexcept : m_settings(format, scope, directoryName, filename) {
	log::info("[cavansite] SettingsManager initialized");
}

SettingsManager::~SettingsManager() noexcept {
	log::info("[cavansite] SettingsManager destroyed");
}


void SettingsManager::addDefaultSetting(std::string key, QVariant value) { // NOLINT(performance-unnecessary-value-param)
	auto [_, inserted] = m_defaults.try_emplace(std::move(key), std::move(value));

	if (!inserted) {
		log::error(
			"[cavansite] SettingsException | Default setting for key '{}' already exists",
			key
		);

		throw except::SettingsException{ "Default setting already exists!" };
	}

	log::debug("[cavansite] Added a default setting for key '{}'", key);

	return;
}


SettingsManager::Setting SettingsManager::read(std::string const& key) const noexcept {
	if (m_settings.contains(key))
			return { .value=(m_settings.value(key)), .source=Setting::Read };

	// setting not in config, falling back to defaults
	if (auto i = m_defaults.find(key); i != m_defaults.end())
		return { .value=((*i).second), .source=Setting::DefaultProvided };
	else
		return { .value={}, .source=Setting::DefaultConstructed };
}

template <bool ThrowOnFail>
SettingsManager::OptIfNoThrow<ThrowOnFail> SettingsManager::readForceDefault(
	std::string const& key
) const noexcept(!ThrowOnFail) {
	auto it = m_defaults.find(key);
	if (it == m_defaults.end()) {
		if constexpr (ThrowOnFail) {
			log::error(
				"[cavansite] SettingsException | Default setting for key '{}' doesn't exists (read)",
				key
			);

			throw except::SettingsException{ "Default setting doesn't exists (read)!" };
		} else {
			log::warn(
				"[cavansite] Default setting for key '{}' doesn't exists (read)",
				key
			);

			return std::nullopt;
		}
	}

	#define CAVANSITE_OPTWRAP(...) if constexpr (ThrowOnFail) return __VA_ARGS__; else return { __VA_ARGS__ }

	if (m_settings.contains(key)) {
		CAVANSITE_OPTWRAP({ .value=(m_settings.value(key)), .source=Setting::Read });
	}

	CAVANSITE_OPTWRAP({ .value=((*it).second), .source=Setting::DefaultProvided });

	#undef CAVANSITE_OPTWRAP
}
template std::optional<SettingsManager::Setting> SettingsManager::readForceDefault<false>(std::string const&) const noexcept;
template SettingsManager::Setting SettingsManager::readForceDefault<true>(std::string const&) const;


void SettingsManager::write(std::string_view key, QVariant const& value) noexcept {
	m_settings.setValue(key, value);

	return;
}

template <bool ThrowOnFail>
SettingsManager::BoolIfNoThrow<ThrowOnFail> SettingsManager::writeForceDefault(
	std::string const& key, QVariant const& value
) noexcept(!ThrowOnFail) {
	if (m_defaults.find(key) == m_defaults.end()) {
		if constexpr (ThrowOnFail) {
			log::error(
				"[cavansite] SettingsException | Default setting for key '{}' doesn't exists (write)",
				key
			);

			throw except::SettingsException{ "Default setting doesn't exists (write)!" };
		} else {
			log::warn(
				"[cavansite] Default setting for key '{}' doesn't exists (write)",
				key
			);

			return false;
		}
	}

	m_settings.setValue(key, value);

	if constexpr (ThrowOnFail)
		return;
	else
		return true;
}
template bool SettingsManager::writeForceDefault<false>(std::string const&, QVariant const&) noexcept;
template void SettingsManager::writeForceDefault<true>(std::string const&, QVariant const&);


void SettingsManager::forceSyncWithDisk() {
	m_settings.sync();

	return;
}