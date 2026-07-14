#include <cavansite/classes/Separator.hpp>

#include <QPainter>
#include <QLinearGradient>

using namespace cavansite;


Separator::Separator(
	Orientation orientation,
	QColor const& color,
	int fadeLength,
	int width,
	QWidget* parent
) : QFrame(parent),
	m_orientation{ orientation }, m_color{ color }, m_fadeLength{ fadeLength } {
	this->setWidth(width);
}


void Separator::setFadeLength(int fadeLength) noexcept {
	if (m_fadeLength != fadeLength) {
		m_fadeLength = fadeLength;
		this->update();
	}

	return;
}

void Separator::setColor(QColor const& color) noexcept {
	if (m_color != color) {
		m_color = color;
		this->update();
	}

	return;
}

int Separator::getWidth() const noexcept {
	return m_orientation == Orientation::Vertical ?
		this->width()
		:
		this->height();
}

void Separator::setWidth(int width) noexcept {
	if (m_orientation == Orientation::Vertical)
		this->setFixedWidth(width);
	else
		this->setFixedHeight(width);

	return;
}


void Separator::paintEvent(QPaintEvent*) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	int totalLength = m_orientation == Orientation::Vertical ?
		this->height()
		:
		this->width();
	auto fadeLength = m_fadeLength;
	int solidLength = totalLength - (2 * fadeLength);
	if (solidLength < 3) {
		solidLength = 3;
		fadeLength = totalLength / 2;
	}

	QLinearGradient grad1;
	QLinearGradient grad2;
	if (m_orientation == Orientation::Vertical) {
		grad1 = QLinearGradient(0, 0, 0, fadeLength);
		grad2 = QLinearGradient(0, totalLength - fadeLength, 0, totalLength);
	} else {
		grad1 = QLinearGradient(0, 0, fadeLength, 0);
		grad2 = QLinearGradient(totalLength - fadeLength, 0, totalLength, 0);
	}

	grad1.setColorAt(0., Qt::transparent);
	grad1.setColorAt(1., m_color);
	grad2.setColorAt(0., m_color);
	grad2.setColorAt(1., Qt::transparent);

	auto width = this->getWidth();
	if (m_orientation == Orientation::Vertical) {
		painter.fillRect(0, 0, width, fadeLength, grad1);
		painter.fillRect(0, fadeLength, width, solidLength, m_color);
		painter.fillRect(0, totalLength - fadeLength, width, fadeLength, grad2);
	} else {
		painter.fillRect(0, 0, fadeLength, width, grad1);
		painter.fillRect(fadeLength, 0, solidLength, width, m_color);
		painter.fillRect(totalLength - fadeLength, 0, fadeLength, width, grad2);
	}

	return;
}