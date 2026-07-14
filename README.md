# cavansite

Offers general purpose classes/utilities I made for using in my Qt apps.

# Features
- Github Actions
    - `Fryy55/cavansite/actions/find-qt-version` for extracting the Qt version from a file
    - `Fryy55/cavansite/actions/build-and-package` for building and packaging Qt apps for different platforms

        Both Actions are made for and supposed to be used with [Fryy55/qt-cmake-template](https://github.com/Fryy55/qt-cmake-template)'s CI
- Breeze themes

    Most themes and theme related scripts/content were vendored from [Alexhuszagh/BreezeStyleSheets](https://github.com/Alexhuszagh/BreezeStyleSheets). See [breeze/](./breeze/) for copyright info

    Keep in mind that _these features are only available with Breeze themes enabled_. See [Breeze Themes](#breeze-themes) for more 
    - `BreezeManager` - a singleton responsible for centralized management of the current state of Breeze themes
    - `BreezeTheme` - an object that describes a theme (colors, modes, etc.)
    - `BreezeThemeWindow` - a built-in settings window for easy, plug-and-play theme configuration for end users
    - `BreezeIconsInterface` - an interface used for dynamic theme update dispatch
- Classes
    - Singletons
        - `SettingsManager` - a singleton responsible for centralized management of your application's settings
    - `CApplication` - a subclass of `QApplication` with built-in exception safety and initialization code for internal cavansite systems. **Heavily recommended to use instead of `QApplication`** (see [!getting-started.md](./docs/!getting-started.md))
    - `HelpButton` - a KDE-inspired help "button" that displays a tooltip on clicking/hovering
    - `Separator` - a visual separator with customizable width, fade length, color and dynamic resizing
- Utilities
    - Exceptions
        - `Exception.hpp` - core exceptions and exception handing utilities
        - Other files - domain-specific exceptions
    - `compileTimeError` - a non-`constexpr` function with no definition; used to trigger compile time errors with an NTTP message
    - `concepts.hpp`
    - `listenForGlobalTheme` - a function to easily add a listener for global theme changes. Redundant with Breeze themes
    - `StructuralString` - a `consteval` string meant to be used as an NTTP
- Extra libraries
    - Uses [Aurora](https://github.com/Fryy55/aurora) as logging base

See [cavansite documentation](./docs/) for more details and examples

# Usage
## Installing
Add the following lines to your `CMakeLists.txt`:

```cmake
CPMAddPackage("gh:Fryy55/cavansite@1.0.0")
target_link_libraries(${PROJECT_NAME} cavansite)
```
Replace `1.0.0` with the version you want to use.

You can also use a specific tag/branch/commit of cavansite like this:

`CPMAddPackage("gh:Fryy55/cavansite#b492c63")` - tag/branch/commit hash

## Using
Simply include headers (e.g. `#include <cavansite/classes/Separator.hpp>`) and use them in your apps!

There is also a general "include everything" header (`<cavansite/cavansite.hpp>`), as well as grouped headers (e.g. `<cavansite/classes/classes.hpp>`).

> [!TIP]
> Normally, every class is located in the `cavansite::*` namespace, however, if you are fine with leaking cavansite to every TU, you can add `set(CAVANSITE_USE_NAMESPACE TRUE)` to your `CMakeLists.txt`. This will precompile the header that solely uses the namespace, thus enabling you to use features directly without explicitly using the namespace everywhere.

### Breeze Themes
If you want to include _Breeze themes_, make sure to:
1) Link against `Qt6::Svg`
2) Set the `CAVANSITE_ADD_BREEZE` variable to _themes you want to include from the following list:_ `red,yellow,orange,green,cyan,blue,purple,pink,mono` (e.g. `set(CAVANSITE_ADD_BREEZE red,blue,mono,purple)`) _before adding the library with CPM_

You can also set the variable to `all` to include all themes (`set(CAVANSITE_ADD_BREEZE all)`)

> [!NOTE]
> Breeze theme enabling/disabling requires `mono` (monochrome) to be included

# License
This project is distributed under the **Apache-2.0 License**.

See `LICENSE` for permissions, conditions and limitations.