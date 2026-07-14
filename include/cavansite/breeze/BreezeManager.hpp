#pragma once

#include <cavansite/breeze/_internal/macro-check.hpp>

#include <cavansite/utils/except/InterfaceException.hpp>
#include <cavansite/breeze/BreezeTheme.hpp>

#include <unordered_set>


namespace cavansite {

class BreezeIconsInterface;

class BreezeManager final {
	friend class BreezeIconsInterface;

public:
	static BreezeManager* get() noexcept;

private:
	BreezeManager() noexcept;

public:
	BreezeManager(BreezeManager const&) = delete;
	BreezeManager& operator=(BreezeManager const&) = delete;
	BreezeManager(BreezeManager&&) = delete;
	BreezeManager& operator=(BreezeManager&&) = delete;

private:
	~BreezeManager() noexcept = default;


public:
	[[nodiscard]] BreezeTheme getTheme() const noexcept;
	void setTheme(BreezeTheme theme, bool writeToSettings = false);

	[[nodiscard]] bool getEnabled() const noexcept { return m_enabled; }
	void setEnabled(bool enabled, bool writeToSettings = false);


private:
	void registerInterface(BreezeIconsInterface* widget);
	void unregisterInterface(BreezeIconsInterface* widget);

private: // Fields
	std::unordered_set<BreezeIconsInterface*> m_interfaces{};
	BreezeTheme m_theme;
	bool m_enabled;
};

} // namespace cavansite