#include <cavansite/classes/CApplication.hpp>

#include <cavansite/classes/singletons/SettingsManager.hpp>
#ifdef CAVANSITE_ADD_BREEZE
	#include <cavansite/breeze/BreezeTheme.hpp>
#endif

#include <aurora/singletons/ThreadManager.hpp>

using namespace cavansite;


#ifdef CAVANSITE_ADD_BREEZE
	static void initBreeze() noexcept {
		Q_INIT_RESOURCE(breeze);

		try {
			SettingsManager::get()->addDefaultSettings(
				SettingsManager::DefaultSettings{
					{ "breeze/theme", BreezeTheme{} },
					{ "breeze/enabled", true }
				}
			);
		} catch (std::exception const& e) {
			utils::handleException(e);
		}

		return;
	}
#endif

CApplication::CApplication(
	int& argc, char** argv, int flags
) noexcept : QApplication(argc, argv, flags) {
	aurora::ThreadManager::get()->addThread("Main");

	#ifdef CAVANSITE_ADD_BREEZE
		initBreeze();
	#endif
}

bool CApplication::notify(QObject* receiver, QEvent* event) noexcept {
	try {
		return QApplication::notify(receiver, event);
	} catch (std::exception const& e) {
		utils::handleException(e);

		return false;
	}
}