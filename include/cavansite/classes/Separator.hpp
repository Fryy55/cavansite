#pragma once

#include <QFrame>


namespace cavansite {

class Separator final : public QFrame {
	Q_OBJECT
	Q_PROPERTY(QColor color READ getColor WRITE setColor)

public:
	enum class Orientation : std::uint8_t {
		Horizontal = 0,
		Vertical = 1
	};

public:
	Separator(
		Orientation orientation = Orientation::Horizontal,
		QColor const& color = Qt::white,
		int fadeLength = 50,
		int width = 3,
		QWidget* parent = nullptr
	);

	Separator(Separator const&) = delete;
	Separator& operator=(Separator const&) = delete;
	Separator(Separator&&) = delete;
	Separator& operator=(Separator&&) = delete;

	~Separator() noexcept override = default;

public:
	[[nodiscard]] int getFadeLength() const noexcept { return m_fadeLength; }
	void setFadeLength(int fadeLength) noexcept;
	[[nodiscard]] QColor const& getColor() const noexcept { return m_color; }
	void setColor(QColor const& color) noexcept;
	[[nodiscard]] int getWidth() const noexcept;
	void setWidth(int width) noexcept;

private:
	void paintEvent(QPaintEvent*) override;

private: // Fields
	QColor m_color;
	int m_fadeLength;
	Orientation m_orientation;
};

} // namespace cavansite