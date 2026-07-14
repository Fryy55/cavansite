#pragma once

#include <QVariant>
#include <QSettings>

#include <unordered_map>
#include <string>


namespace cavansite {

class SettingsManager final {
public:
	static SettingsManager* get();
	static bool init(
		QString const& directoryName, QString const& filename,
		QSettings::Format format = QSettings::IniFormat,
		QSettings::Scope scope = QSettings::UserScope
	) noexcept;

private:
	struct Delete final {
		void operator()(SettingsManager*) const noexcept;
	};
	static inline std::unique_ptr<SettingsManager, Delete> s_instance{ nullptr };

	SettingsManager(
		QString const&, QString const&,
		QSettings::Format, QSettings::Scope
	) noexcept;

public:
	SettingsManager(SettingsManager const&) = delete;
	SettingsManager& operator=(SettingsManager const&) = delete;
	SettingsManager(SettingsManager&&) = delete;
	SettingsManager& operator=(SettingsManager&&) = delete;

private:
	~SettingsManager() noexcept;


public:
	void addDefaultSetting(std::string key, QVariant value);

	using DefaultSettings = std::vector<std::pair<std::string, QVariant>>;

	void addDefaultSettings(
		std::convertible_to<DefaultSettings> auto&& keyValuePairs
	) {
		using ForwardType = decltype(keyValuePairs);

		for (auto&& [key, value] : keyValuePairs) {
			this->addDefaultSetting(
				std::forward_like<ForwardType>(key),
				std::forward_like<ForwardType>(value)
			);
		}

		return;
	}


	struct Setting final {
		enum Source : std::uint8_t {
			Read,
			DefaultProvided,
			DefaultConstructed
		};

		QVariant value;
		Source source;
	};

	[[nodiscard]] Setting read(std::string const& key) const noexcept;

	template <bool ThrowOnFail>
	using OptIfNoThrow = std::conditional_t<
		ThrowOnFail,
		Setting, std::optional<Setting>
	>;

	template <bool ThrowOnFail = true>
	[[nodiscard]] OptIfNoThrow<ThrowOnFail> readForceDefault(
		std::string const& key
	) const noexcept(!ThrowOnFail);


	void write(std::string_view key, QVariant const& value) noexcept;

	template <bool ThrowOnFail>
	using BoolIfNoThrow = std::conditional_t<ThrowOnFail, void, bool>;

	template <bool ThrowOnFail = true>
	BoolIfNoThrow<ThrowOnFail> writeForceDefault(
		std::string const& key, QVariant const& value
	) noexcept(!ThrowOnFail);


	void forceSyncWithDisk();

private:
	std::unordered_map<std::string, QVariant> m_defaults{};
	QSettings m_settings;
};

} // namespace cavansite