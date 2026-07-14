#include <cavansite/utils/except/Exception.hpp>

#include <QMessageBox>
#include <QApplication>

#include <aurora/log.hpp>


void cavansite::utils::handleException(std::exception const& exception) noexcept {
	aurora::log::info("[cavansite] Exception reached the handler: '{}'", exception.what());

	QMessageBox popup(nullptr);
	popup.setIcon(QMessageBox::Critical);
	popup.setWindowTitle("Unhandled exception!");
	popup.setText(std::format("An unhandled exception has occurred:\n{}", exception.what()).c_str());
	popup.exec();

	if (auto a = qApp) {
		QMetaObject::invokeMethod(
			a, [] static { QCoreApplication::exit(1); },
			Qt::QueuedConnection
		);
	}

	return;
}