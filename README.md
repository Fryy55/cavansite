# cavansite

Offers general purpose classes/utilities I made for using in my Qt apps.

# Features
- Github Actions
    - `Fryy55/cavansite/actions/find-qt-version` for extracting the Qt version from a file
    - `Fryy55/cavansite/actions/build-and-package` for building and packaging Qt apps for different platforms
    <br>Both Actions are made for and supposed to be used with [Fryy55/qt-cmake-template](https://github.com/Fryy55/qt-cmake-template)'s CI
- Extra libraries
    - Uses [Aurora](https://github.com/Fryy55/aurora) as logging base

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
Simply include headers (e.g. `#include <cavansite/classes/Separator.hpp>`) and use them in your mods!

There is also a general "include everything" header (`<cavansite/cavansite.hpp>`), as well as grouped headers (e.g. `<cavansite/classes/classes.hpp>`).

> [!TIP]
> Normally, every class is located in the `cavansite::*` namespace, however, if you are fine with leaking cavansite to every TU, you can add `set(CAVANSITE_USE_NAMESPACE TRUE)` to your `CMakeLists.txt`. This will precompile the header that solely uses the namespace, thus enabling you to use features directly without explicitly using the namespace everywhere.

### Breeze Themes
If you want to include the _Breeze_ theme, make sure to:
1) Link against `Qt6::Svg`
2) Set the `CAVANSITE_ADD_BREEZE` variable to _themes you want to include from [this list](https://github.com/Alexhuszagh/BreezeStyleSheets/tree/main/theme)_ (e.g. `set(CAVANSITE_ADD_BREEZE light-purple-alt,dark-purple-alt)`) _before adding the library with CPM_

You can also set the variable to `all` to include all themes

# License
This project is distributed under the **Apache-2.0 License**.

See `LICENSE` for permissions, conditions and limitations.