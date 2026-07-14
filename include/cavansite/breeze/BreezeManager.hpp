#pragma once

#include <cavansite/breeze/impl/macro-check.hpp>

#include <cavansite/utils/except/InterfaceException.hpp>
#include <cavansite/breeze/BreezeTheme.hpp>

#include <atomic>
#include <unordered_set>


namespace cavansite {

class BreezeIconsInterface;

class BreezeManager final {
	friend class BreezeIconsInterface;

public:
	static BreezeManager* get() noexcept;
	static bool isDestroyed() noexcept;

private:
	BreezeManager() noexcept;

public:
	BreezeManager(BreezeManager const&) = delete;
	BreezeManager& operator=(BreezeManager const&) = delete;
	BreezeManager(BreezeManager&&) = delete;
	BreezeManager& operator=(BreezeManager&&) = delete;

private:
	~BreezeManager() noexcept;


public:
	[[nodiscard]] BreezeTheme getTheme() const noexcept { return m_theme; }
	void setTheme(BreezeTheme theme);

	[[nodiscard]] bool getEnabled() const noexcept { return m_enabled; }
	void setEnabled(bool enabled);


private:
	void registerInterface(BreezeIconsInterface* widget);
	void unregisterInterface(BreezeIconsInterface* widget);

// Fields
private:
	static inline std::atomic_bool s_destroyed{ false };

	std::unordered_set<BreezeIconsInterface*> m_interfaces{};
	BreezeTheme m_theme;
	bool m_enabled;
};

} // namespace cavansite