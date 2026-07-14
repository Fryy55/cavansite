#pragma once

#include <QLabel>


namespace cavansite {

class HelpButton final : public QLabel {
	Q_OBJECT

public:
	HelpButton(QWidget* parent = nullptr, Qt::WindowFlags flags = {});
	HelpButton(
		QString const& tooltip,
		QWidget* parent = nullptr,
		Qt::WindowFlags flags = {}
	);

	HelpButton(HelpButton const&) = delete;
	HelpButton& operator=(HelpButton const&) = delete;
	HelpButton(HelpButton&&) = delete;
	HelpButton& operator=(HelpButton&&) = delete;
	
	~HelpButton() noexcept override = default;

private:
	bool event(QEvent*) override;
};

} // namespace cavansite