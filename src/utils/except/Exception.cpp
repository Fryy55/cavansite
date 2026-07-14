#include <cavansite/utils/except/Exception.hpp>

#include <QMessageBox>
#include <QApplication>


static cavansite::utils::ExceptionHandler s_exceptionHandler{};

void cavansite::utils::handleException(std::exception const& exception) noexcept {
	if (s_exceptionHandler) {
		s_exceptionHandler(exception);

		return;
	}

	aurora::log::warn("[cavansite] Exception reached the handler: '{}'", exception.what());

	QMessageBox popup{};
	popup.setIcon(QMessageBox::Critical);
	popup.setWindowTitle("Unhandled exception!");
	popup.setText(std::format("<b>An unhandled exception has occurred</b><br><br>{}", exception.what()).c_str());
	popup.exec();

	if (auto a = qApp) {
		QMetaObject::invokeMethod(
			a, [] static { QCoreApplication::exit(1); },
			Qt::QueuedConnection
		);
	} else {
		std::exit(1);
	}

	return;
}

void cavansite::utils::setExceptionHandler(ExceptionHandler&& handler) noexcept {
	s_exceptionHandler = std::move(handler);

	return;
}