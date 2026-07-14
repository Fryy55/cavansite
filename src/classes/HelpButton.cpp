#include <cavansite/classes/HelpButton.hpp>

#include <QToolTip>
#include <QApplication>

using namespace cavansite;


HelpButton::HelpButton(QWidget* parent) : QPushButton(parent) {
	#ifdef CAVANSITE_ADD_BREEZE
		auto [prefix, theme] = this->registerBreezeInterface();

		this->themeUpdate(prefix, theme);
	#else
		utils::listenForGlobalTheme(this, &HelpButton::themeUpdate);

		this->themeUpdate();
	#endif

	this->setStyleSheet("QPushButton:!hover { border: none; }");
	this->setCursor(Qt::WhatsThisCursor);
	connect(this, &QPushButton::clicked, this, &HelpButton::onClick);
}

HelpButton::HelpButton(QString const& tooltip, QWidget* parent) : HelpButton(parent) {
	this->setToolTip(tooltip);
}


void HelpButton::onClick() noexcept {
	auto tooltipText = this->toolTip();
	QToolTip::showText({ 0, 0 }, tooltipText);

	QWidget* tooltip = nullptr;
	for (auto widget : QApplication::topLevelWidgets()) {
		if (strcmp(widget->metaObject()->className(), "QTipLabel") == 0) {
			tooltip = widget;
			break;
		}
	}

	QPoint pos{ 0, 0 };
	if (tooltip)
		pos = { -(tooltip->width() - this->width()) / 2, -(this->height() * 2) };

	QToolTip::showText(this->mapToGlobal(pos), tooltipText, this);
}

#ifdef CAVANSITE_ADD_BREEZE
void HelpButton::themeUpdate(QString const&, BreezeTheme theme) {
	this->setIcon(QIcon{
		theme.m_realMode == BreezeTheme::Mode::Dark ?
			":/cavansite/ui/help-button-d"
			:
			":/cavansite/ui/help-button-l"
	});

	return;
}
#else
void HelpButton::themeUpdate(Qt::ColorScheme mode) noexcept {
	this->setIcon(QIcon{
		mode == Qt::ColorScheme::Dark ?
			":/cavansite/ui/help-button-d"
			:
			":/cavansite/ui/help-button-l"
	});
}
#endif