#ifdef CAVANSITE_ADD_BREEZE


#include <cavansite/breeze/BreezeThemeWindow.hpp>

#include <cavansite/classes/HelpButton.hpp>

#include <QPushButton>
#include <QLabel>
#include <QRadioButton>
#include <QCheckBox>
#include <QKeyEvent>

using namespace cavansite;
using namespace Qt::StringLiterals;


BreezeThemeWindow::BreezeThemeWindow(
	QWidget* parent
) : QWidget(parent, Qt::Window) {
	this->setWindowModality(Qt::WindowModal);
	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setWindowTitle("Select a Theme");

	auto mainLayout = new QVBoxLayout(this);

	#ifdef CAVANSITE_BREEZE_THEME_MONO
		mainLayout->addLayout(this->createThemeToggleSettings());
		mainLayout->addSpacing(15);
	#endif
	mainLayout->addLayout(this->createThemeColorSettings());
	mainLayout->addSpacing(15);
	mainLayout->addLayout(this->createThemeModeSettings());
	mainLayout->addSpacing(15);
	mainLayout->addLayout(this->createThemeAltSettings());
	mainLayout->addSpacing(30);

	mainLayout->addStretch();

	auto closeBtn = new QPushButton("Done");
	closeBtn->setFixedWidth(closeBtn->sizeHint().width() * 1.5f);
	connect(closeBtn, &QPushButton::clicked, [this] { this->close(); });
	mainLayout->addWidget(closeBtn, 0, Qt::AlignCenter);
}

QHBoxLayout* BreezeThemeWindow::createThemeToggleSettings() const {
	auto ret = new QHBoxLayout();

	ret->addStretch();

	auto check = new QCheckBox("Toggle Breeze Theme");
	connect(check, &QCheckBox::toggled, [](bool checked) static {
		
	});
	ret->addWidget(check);

	ret->addStretch();

	return ret;
}

QVBoxLayout* BreezeThemeWindow::createThemeColorSettings() const {
	auto ret = new QVBoxLayout();

	ret->addWidget(new QLabel("Breeze Theme Color"), 0, Qt::AlignLeft);


	auto layout = new QHBoxLayout();

	auto createButton = [layout](std::string_view theme, std::optional<QString> tooltip = std::nullopt) {
		auto ret = new QPushButton();

		ret->setIcon(QIcon(u":/dark-"_s % QString::fromLatin1(theme) % u"/radio_checked.svg"_s));
		ret->setToolTip(
			tooltip ?
				tooltip.value()
				:
				QString{ static_cast<char>(std::toupper(theme[0z])) } % QString::fromLatin1(theme.substr(1z))
		);

		return ret;
	};

	#ifdef CAVANSITE_BREEZE_THEME_RED
		layout->addWidget(createButton("red"));
	#endif
	#ifdef CAVANSITE_BREEZE_THEME_ORANGE
		layout->addWidget(createButton("orange"));
	#endif
	#ifdef CAVANSITE_BREEZE_THEME_YELLOW
		layout->addWidget(createButton("yellow"));
	#endif
	#ifdef CAVANSITE_BREEZE_THEME_GREEN
		layout->addWidget(createButton("green"));
	#endif
	#ifdef CAVANSITE_BREEZE_THEME_CYAN
		layout->addWidget(createButton("cyan"));
	#endif
	#ifdef CAVANSITE_BREEZE_THEME_BLUE
		layout->addWidget(createButton("blue"));
	#endif
	#ifdef CAVANSITE_BREEZE_THEME_PURPLE
		layout->addWidget(createButton("purple"));
	#endif
	#ifdef CAVANSITE_BREEZE_THEME_PINK
		layout->addWidget(createButton("pink"));
	#endif
	#ifdef CAVANSITE_BREEZE_THEME_MONO
		layout->addWidget(createButton("mono", "Monochrome"));
	#endif

	ret->addLayout(layout);


	return ret;
}

QVBoxLayout* BreezeThemeWindow::createThemeModeSettings() const {
	auto ret = new QVBoxLayout();

	ret->addWidget(new QLabel("Theme Mode"), 0, Qt::AlignLeft);


	auto layout = new QHBoxLayout();

	auto light = new QRadioButton("Light");
	light->setIcon(QIcon{ ":/_cavansite/breeze/light-d" });
	layout->addWidget(light);

	auto dark = new QRadioButton("Dark");
	dark->setIcon(QIcon{ ":/_cavansite/breeze/dark-d" });
	layout->addWidget(dark);

	auto system = new QRadioButton("System");
	system->setIcon(QIcon{ ":/_cavansite/breeze/auto-d" });
	layout->addWidget(system);

	ret->addLayout(layout);


	return ret;
}

QVBoxLayout* BreezeThemeWindow::createThemeAltSettings() const {
	auto ret = new QVBoxLayout();


	auto layout = new QHBoxLayout();

	auto altLabel = new QLabel("Alt Colors");
	layout->addWidget(altLabel);

	auto tipBtn = new HelpButton("Alternative themes feature slightly different visuals");
	tipBtn->setPixmap(QPixmap(":/dark-purple/dialog_help.svg"));
	std::int32_t dimension = altLabel->sizeHint().height() * 0.6;
	tipBtn->setFixedSize(dimension, dimension);
	layout->addWidget(tipBtn);

	layout->addSpacing(tipBtn->size().width());

	auto checkbox = new QCheckBox();
	layout->addWidget(checkbox);

	layout->addStretch();


	ret->addLayout(layout);


	return ret;
}


void BreezeThemeWindow::keyPressEvent(QKeyEvent* e) {
	if (e->key() == Qt::Key_Escape)
		this->close();

	return;
}


#endif // CAVANSITE_ADD_BREEZE