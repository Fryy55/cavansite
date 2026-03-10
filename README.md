# cavansite

Offers general purpose classes/utilities I made for using in my Qt apps.

# Features
- Github Actions
    - 

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
Simply include headers (e.g. `#include <cavansite//.hpp>`) and use them in your mods!

There is also a general "include everything" header (`<cavansite/cavansite.hpp>`), as well as grouped headers (e.g. `<cavansite//.hpp>`).

> [!TIP]
> Normally, every class is located in the `cavansite::*` namespace, however, if you are fine with leaking cavansite to every TU, you can add `set(CAVANSITE_USE_NAMESPACE TRUE)` to your `CMakeLists.txt`. This will precompile the header that solely uses the namespace, thus enabling you to use features directly without explicitly using the namespace everywhere.

# License
This project is distributed under the **Apache-2.0 License**.

See `LICENSE` for permissions, conditions and limitations.