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

	template <std::derived_from<QObject> WinT, typename ...Args>
		requires std::constructible_from<WinT, Args...>
	[[nodiscard]] std::unique_ptr<WinT> createMainWindow(Args&&... args) noexcept {
		try {
			auto w = std::make_unique<WinT>(std::forward<Args>(args)...);

			w->show();

			return w;
		} catch (std::exception const& e) {
			utils::handleException(e);

			return nullptr;
		}
	}
};

} // namespace cavansite