#ifdef CAVANSITE_ADD_BREEZE


#include <cavansite/breeze/BreezeThemeWindow.hpp>

#include <cavansite/breeze/BreezeManager.hpp>
#include <cavansite/classes/HelpButton.hpp>

#include <QLabel>
#include <QRadioButton>
#include <QCheckBox>
#include <QKeyEvent>
#include <QPropertyAnimation>

using namespace cavansite;
using namespace Qt::StringLiterals;


BreezeThemeWindow::BreezeThemeWindow(
	QWidget* parent
) : QWidget(parent, Qt::Window) {
	auto [prefix, theme] = this->registerBreezeInterface();
	this->setWindowModality(Qt::WindowModal);
	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setWindowTitle("Select a Theme");

	auto mainLayout = new QVBoxLayout(this);
	auto settingsBox = new QGroupBox();
	auto toggledLayout = new QVBoxLayout(settingsBox);

	#ifdef CAVANSITE_BREEZE_THEME_MONO
		settingsBox->setTitle("Toggle Breeze Theme");
		settingsBox->setCheckable(true);
		settingsBox->setChecked(BreezeManager::get()->getEnabled());
		connect(settingsBox, &QGroupBox::clicked, [](bool checked) static {
			BreezeManager::get()->setEnabled(checked, true);
		});
	#endif
	toggledLayout->addWidget(this->createThemeColorSettings(theme));
	toggledLayout->addSpacing(10);
	toggledLayout->addWidget(this->createThemeModeSettings(theme));
	toggledLayout->addSpacing(15);
	toggledLayout->addLayout(this->createThemeAltSettings());
	mainLayout->addWidget(settingsBox);

	mainLayout->addSpacing(15);
	m_separator = new Separator(Separator::Orientation::Horizontal, Qt::transparent, 400);
	mainLayout->addWidget(m_separator);

	mainLayout->addSpacing(45);
	mainLayout->addStretch();

	auto closeBtn = new QPushButton("Done");
	closeBtn->setFixedWidth(closeBtn->sizeHint().width() * 1.5f);
	connect(closeBtn, &QPushButton::clicked, [this] { this->close(); });
	mainLayout->addWidget(closeBtn, 0, Qt::AlignCenter);

	this->themeUpdate(prefix, theme);
}

QGroupBox* BreezeThemeWindow::createThemeColorSettings(BreezeTheme const& theme) {
	auto ret = new QGroupBox("Breeze Theme Color");

	auto layout = new QHBoxLayout(ret);
	auto currentColor = theme.m_color;
	std::uint8_t buttonCount = 0u;

	auto createButton = [this, currentColor, layout, &buttonCount]<utils::StructuralString themeStr>(std::optional<QString> tooltip = std::nullopt) {
		auto ret = new QPushButton();
		constexpr auto themeSV = themeStr.string();
		constexpr auto color = colorForTheme(themeSV);
		#ifdef CAVANSITE_BREEZE_THEME_MONO
			if constexpr (color == BreezeTheme::Color::Monochrome)
				m_monoButton = ret;
		#endif

		ret->setToolTip(std::move(tooltip).value_or(
			QString{ static_cast<char>(std::toupper(themeSV[0z])) } % QString::fromLatin1(themeSV.substr(1z))
		));
		bool enabled = currentColor == color;
		ret->setProperty("cavansite/enabled", enabled);
		QString iconString{ u":/dark-"_s % QString::fromLatin1(themeSV) % u"/radio_"_s };
		ret->setProperty("cavansite/on-icon", QIcon{ iconString % u"checked.svg"_s });
		ret->setProperty("cavansite/off-icon", QIcon{ iconString % u"unchecked.svg"_s });
		ret->setIcon(ret->property(enabled ? "cavansite/on-icon" : "cavansite/off-icon").value<QIcon>());

		connect(ret, &QPushButton::clicked, [color, this, ret] {
			auto bm = BreezeManager::get();

			auto theme = bm->getTheme();
			theme.m_color = color;
			bm->setTheme(theme, true);

			for (auto button : m_buttons) {
				if (button->property("cavansite/enabled").toBool()) {
					button->setProperty("cavansite/enabled", false);
					button->setIcon(button->property("cavansite/off-icon").value<QIcon>());

					break;
				}
			}
			ret->setProperty("cavansite/enabled", true);
			ret->setIcon(ret->property("cavansite/on-icon").value<QIcon>());
		});

		m_buttons[buttonCount++] = ret;

		return ret;
	};

	#ifdef CAVANSITE_BREEZE_THEME_RED
		layout->addWidget(createButton.operator()<"red">());
	#endif
	#ifdef CAVANSITE_BREEZE_THEME_ORANGE
		layout->addWidget(createButton.operator()<"orange">());
	#endif
	#ifdef CAVANSITE_BREEZE_THEME_YELLOW
		layout->addWidget(createButton.operator()<"yellow">());
	#endif
	#ifdef CAVANSITE_BREEZE_THEME_GREEN
		layout->addWidget(createButton.operator()<"green">());
	#endif
	#ifdef CAVANSITE_BREEZE_THEME_CYAN
		layout->addWidget(createButton.operator()<"cyan">());
	#endif
	#ifdef CAVANSITE_BREEZE_THEME_BLUE
		layout->addWidget(createButton.operator()<"blue">());
	#endif
	#ifdef CAVANSITE_BREEZE_THEME_PURPLE
		layout->addWidget(createButton.operator()<"purple">());
	#endif
	#ifdef CAVANSITE_BREEZE_THEME_PINK
		layout->addWidget(createButton.operator()<"pink">());
	#endif
	#ifdef CAVANSITE_BREEZE_THEME_MONO
		layout->addWidget(createButton.operator()<"mono">("Monochrome"));
	#endif

	return ret;
}

QGroupBox* BreezeThemeWindow::createThemeModeSettings(BreezeTheme const& theme) {
	auto ret = new QGroupBox("Theme Mode");

	auto layout = new QHBoxLayout(ret);

	m_light = new QRadioButton("Light");
	connect(m_light, &QRadioButton::clicked, [](bool checked) static {
		if (auto bm = BreezeManager::get(); checked) {
			auto theme = bm->getTheme();
			theme.setMode(BreezeTheme::Mode::Light);
			bm->setTheme(theme, true);
		}
	});
	layout->addWidget(m_light);

	layout->addStretch();

	m_dark = new QRadioButton("Dark");
	connect(m_dark, &QRadioButton::clicked, [](bool checked) static {
		if (auto bm = BreezeManager::get(); checked) {
			auto theme = bm->getTheme();
			theme.setMode(BreezeTheme::Mode::Dark);
			bm->setTheme(theme, true);
		}
	});
	layout->addWidget(m_dark);

	layout->addStretch();

	m_system = new QRadioButton("System");
	connect(m_system, &QRadioButton::clicked, [](bool checked) static {
		if (auto bm = BreezeManager::get(); checked) {
			auto theme = bm->getTheme();
			theme.setMode(BreezeTheme::Mode::System);
			bm->setTheme(theme, true);
		}
	});
	layout->addWidget(m_system);

	switch (theme.m_providedMode) {
		case BreezeTheme::Mode::Dark:
			m_dark->setChecked(true);
			break;

		case BreezeTheme::Mode::Light:
			m_light->setChecked(true);
			break;

		case BreezeTheme::Mode::System:
			m_system->setChecked(true);
			break;

		default:
			throw except::Exception{ "Unhandled Breeze theme mode!" };
	}

	return ret;
}

QVBoxLayout* BreezeThemeWindow::createThemeAltSettings() const {
	auto ret = new QVBoxLayout();


	auto layout = new QHBoxLayout();

	auto checkbox = new QCheckBox("Alt Colors");
	checkbox->setChecked(BreezeManager::get()->getTheme().m_alt);
	connect(checkbox, &QCheckBox::clicked, [](bool checked) static {
		auto bm = BreezeManager::get();

		auto theme = bm->getTheme();
		theme.m_alt = checked;
		bm->setTheme(theme, true);
	});
	layout->addWidget(checkbox);

	auto tipBtn = new HelpButton("Alternative themes feature slightly different visuals");
	layout->addWidget(tipBtn);

	layout->addStretch();


	ret->addLayout(layout);


	return ret;
}


void BreezeThemeWindow::keyPressEvent(QKeyEvent* e) {
	if (e->key() == Qt::Key_Escape)
		this->close();

	return;
}

void BreezeThemeWindow::themeUpdate(QString const&, BreezeTheme theme) {
	bool dark = theme.m_realMode == BreezeTheme::Mode::Dark;

	#ifdef CAVANSITE_BREEZE_THEME_MONO
		QString iconString{
			u":/"_s
			%
			(dark ? u"dark"_s : u"light"_s)
			%
			u"-mono/radio_"_s
		};
		m_monoButton->setProperty("cavansite/on-icon", QIcon{ iconString % u"checked.svg"_s });
		m_monoButton->setProperty("cavansite/off-icon", QIcon{ iconString % u"unchecked.svg"_s });
		m_monoButton->setIcon(m_monoButton->property(
			m_monoButton->property("cavansite/enabled").toBool() ? "cavansite/on-icon" : "cavansite/off-icon"
		).value<QIcon>());
	#endif

	if (dark) {
		m_light->setIcon(QIcon{ ":/cavansite/breeze/light-d" });
		m_dark->setIcon(QIcon{ ":/cavansite/breeze/dark-d" });
		m_system->setIcon(QIcon{ ":/cavansite/breeze/auto-d" });
	} else {
		m_light->setIcon(QIcon{ ":/cavansite/breeze/light-l" });
		m_dark->setIcon(QIcon{ ":/cavansite/breeze/dark-l" });
		m_system->setIcon(QIcon{ ":/cavansite/breeze/auto-l" });
	}

	auto anim = new QPropertyAnimation(m_separator, "color");
	anim->setDuration(200);
	anim->setStartValue(m_separator->getColor());
	anim->setEndValue(theme.getAccentColor());
	anim->start(QAbstractAnimation::DeleteWhenStopped);

	return;
}


#endif // CAVANSITE_ADD_BREEZE