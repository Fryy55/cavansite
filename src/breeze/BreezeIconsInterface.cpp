#ifdef CAVANSITE_ADD_BREEZE


#include <cavansite/breeze/BreezeIconsInterface.hpp>

#include <cavansite/breeze/BreezeManager.hpp>

using namespace cavansite;


BreezeIconsInterface::~BreezeIconsInterface() noexcept {
	if (!BreezeManager::isDestroyed()) {
		try {
			BreezeManager::get()->unregisterInterface(this);
		} catch (except::InterfaceException const& e) {
			utils::handleException(e);
		}
	}
}


std::pair<QString, BreezeTheme> BreezeIconsInterface::registerBreezeInterface() {
	auto bm = BreezeManager::get();

	bm->registerInterface(this);

	auto theme = bm->getTheme();

	return { theme.getPrefix(), theme };
}


#endif // CAVANSITE_ADD_BREEZE