# Getting Started With cavansite Breeze Themes
After you enable Breeze themes as described in [README.md](../../README.md) you should be all set. Make sure to initialize [SettingsManager](../classes/singletons/SettingsManager.md) as cavansite uses settings to persistently save the selected Breeze theme

To easily provide a user-friendly interface for Breeze theme configuration cavansite provides `BreezeThemeWindow`. Code below creates and shows that window on button click:

```c++
connect(button, &QPushButton::clicked, [this] {
    (new BreezeThemeWindow(this))->show();
});
```

> [!NOTE]
> It is _highly recommended_ that you set the _window that creates `BreezeThemeWindow`_ as its parent (`this` in the example). This is due to `BreezeThemeWindow` being window-modal and blocking all input from a parent window, preventing creation of multiple configuration windows and wacky behavior if set as a parent


# Macros
Enabling Breeze themes automatically defines a number of macros:

- `CAVANSITE_ADD_BREEZE` is defined if at least one Breeze theme is enabled, undefined if no Breeze themes are enabled (if Breeze themes are disabled). If defined its value is the number of Breeze themes enabled
- A `CAVANSITE_BREEZE_THEME_X` macro for every theme that's enabled. Currently with **CMake's** `CAVANSITE_ADD_BREEZE` set to `all`, all possible macros are:
    - `CAVANSITE_BREEZE_THEME_RED`
    - `CAVANSITE_BREEZE_THEME_ORANGE`
    - `CAVANSITE_BREEZE_THEME_YELLOW`
    - `CAVANSITE_BREEZE_THEME_GREEN`
    - `CAVANSITE_BREEZE_THEME_CYAN`
    - `CAVANSITE_BREEZE_THEME_BLUE`
    - `CAVANSITE_BREEZE_THEME_PURPLE`
    - `CAVANSITE_BREEZE_THEME_PINK`
    - `CAVANSITE_BREEZE_THEME_MONO`


# Working With Themes
`BreezeTheme` is a class that describes a Breeze theme. At any given moment you can inspect its members for the color, provided mode (`Dark`/`Light`/`System`; the mode that was provided during theme construction), real mode (could only be `Dark`/`Light`; the mode you should normally rely on) and whether or not the theme is an alt theme. You can also get an accent color for the theme and set a mode with automatic inferring of a real mode with member functions

You can get the current theme at any given moment with `BreezeManager` - a singleton that controls current Breeze theme state. You can also set a theme using this singleton and get/set the enabled state of themes. When disabled, the theme that your application uses is the system theme. Setters for both theme and enabled state include a `bool` parameter that dictates whether or not to save the value as the setting and defaults to `false`

To massively simplify theme updating for your widgets cavansite provides a `BreezeIconsInterface` class. It is an abstract class that contains 2 functions - `registerBreezeInterface` and a pure virtual `themeUpdate`. `BreezeManager` has a widget registration system - widgets that are registered at a given moment will get their `themeUpdate` called if a theme update happens (which also includes system theme changes). `BreezeManager` automatically determines what theme everything should be set to - everything you need to do is to use the theme info to update your theme! Theme _unregistering_ happens automatically with a destructor and you never have to care about it. _Registering_, however, is manual, and you need to (preferably) do it in the constructor. Thankfully, as for many of cavansite's systems, forgetting to register your widget or accidentally registering twice will throw an exception, so you will never miss a registration. An accidental benefit of manual registration is the fact that it provides you a current _prefix_ and a current _theme_, which also happen to be the parameters for `themeUpdate`. A prefix is a part of the resource string you can use to automatically access correct assets from Breeze themes. For example, prefix `":/dark-purple"` will be sent if your currently selected theme is purple in dark mode. You can concatenate it with Breeze resources (e.g. `QString{ prefix % "/dialog_save.svg" }` inside `themeUpdate`) to use resources in a theme agnostic way without ever manually querying `BreezeManager`. Prefix can also be generated from an arbitrary `BreezeTheme` at any time using the `getPrefix()` member function

> [!NOTE]
> Prefixes work correctly even when Breeze themes are disabled - in this case the prefix/theme that's sent is monochrome theme (since it's the most neutral color), which is the reason theme disabling is only available when monochrome theme is enabled

> [!TIP]
> You can find Breeze resources available for use by configuring your CMake project, checking `build-folder/breeze-generated-themes/dist` and going to any theme's folder. All svg files from all folders are universally available and can be used in a theme agnostic manner with prefixes or individually with hardcoded theme paths (e.g. `":/dark-blue/down_arrow_hover.svg"`) if you need a specific color

```c++
class Example final : public cavansite::BreezeIconsInterface {
public:
    Example() {
        auto [prefix, theme] = this->registerBreezeInterface();

        // set up your widgets

        this->themeUpdate(prefix, theme);
    }

private:
    void themeUpdate(QString const& prefix, cavansite::BreezeTheme theme) override {
        // update widgets based on prefix and theme info
    }
}
```