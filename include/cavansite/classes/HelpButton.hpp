#pragma once

#ifdef CAVANSITE_ADD_BREEZE
	#include <cavansite/breeze/BreezeIconsInterface.hpp>
#else
	#include <cavansite/utils/listenForGlobalTheme.hpp>
#endif

#include <QPushButton>


namespace cavansite {

class HelpButton final : public QPushButton
#ifdef CAVANSITE_ADD_BREEZE
	, public BreezeIconsInterface
#endif
{
	Q_OBJECT

public:
	HelpButton(QWidget* parent = nullptr);
	HelpButton(QString const& tooltip, QWidget* parent = nullptr);

	HelpButton(HelpButton const&) = delete;
	HelpButton& operator=(HelpButton const&) = delete;
	HelpButton(HelpButton&&) = delete;
	HelpButton& operator=(HelpButton&&) = delete;
	
	~HelpButton() noexcept override = default;

private:
	void onClick() noexcept;

#ifdef CAVANSITE_ADD_BREEZE
	void themeUpdate(QString const&, BreezeTheme) override;
#else
	void themeUpdate(CAVANSITE_GLOBAL_THEME_PARAM) noexcept;
#endif

private: // Fields
	bool m_showingTooltip = false;
};

} // namespace cavansite