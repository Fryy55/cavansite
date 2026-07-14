#include <cavansite/classes/HelpButton.hpp>

#include <QEvent>
#include <QToolTip>

using namespace cavansite;


HelpButton::HelpButton(
	QWidget* parent,
	Qt::WindowFlags flags
) : QLabel(parent, flags) {
	this->setAttribute(Qt::WA_Hover, true);
	this->setScaledContents(true);
}

HelpButton::HelpButton(
	QString const& tooltip,
	QWidget* parent,
	Qt::WindowFlags flags
) : HelpButton(parent, flags) {
	this->setToolTip(tooltip);
}

bool HelpButton::event(QEvent* e) {
	switch (e->type()) {
		case QEvent::ToolTip:
			return true;

		case QEvent::HoverEnter: [[fallthrough]];
		case QEvent::MouseButtonPress:
			QToolTip::showText(this->mapToGlobal(QPoint{ 0, 0 }), this->toolTip());
			return true;

		default:
			return QLabel::event(e);
	}
}