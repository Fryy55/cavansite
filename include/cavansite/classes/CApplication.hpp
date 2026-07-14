#pragma once

#include <QApplication>

#include <cavansite/utils/except/Exception.hpp>


namespace cavansite {

class CApplication final : public QApplication {
public:
	CApplication(int& argc, char** argv, int flags = ApplicationFlags) noexcept;
	
	CApplication(CApplication const&) = delete;
	CApplication& operator=(CApplication const&) = delete;
	CApplication(CApplication&&) = delete;
	CApplication& operator=(CApplication&&) = delete;
	
	~CApplication() noexcept override = default;
	

public:
	bool notify(QObject* receiver, QEvent* event) noexcept override;

	template <std::derived_from<QObject> WinT, bool Show = true, typename ...Args>
		requires std::constructible_from<WinT, Args...>
	[[nodiscard("Returned `std::unique_ptr` will be destroyed if you don't save it to a variable or release it")]]
	static std::unique_ptr<WinT> createMainWindow(Args&&... args) noexcept {
		try {
			auto w = std::make_unique<WinT>(std::forward<Args>(args)...);

			if constexpr (Show)
				w->show();

			return w;
		} catch (std::exception const& e) {
			utils::handleException(e);

			return nullptr;
		}
	}
};

} // namespace cavansite