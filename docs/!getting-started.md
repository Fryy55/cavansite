# Getting Started With cavansite
Before your application can be started, some cavansite systems need to go through specific initialization steps. Some of those are handled automatically when you use special classes, but some require manual configuration. In any way, if you forget to initialize something you will most likely notice it - cavansite uses a _fail-fast_ design, meaning forgotten steps will likely be met with an exception on your first testing launch

Due to this, _exception safety_ is a core design point in cavansite's classes. Exceptions are used in places where a _developer_ clearly messed up and fundamental application logic is obviously flawed, meaning ideally you will _not_ get any exceptions in real, production-possible situations. Still though, it's preferred you keep exceptions enabled for your production builds, as the binary bloat is negligible in most GUI applications and cavansite provides robust exception handing systems

The first (and, arguably, most important) class you need to pay attention to is `CApplication`. This class can directly replace `QApplication` in your code and flawlessly handles all exceptions thrown from your application's event-related systems. `CApplication` also has a helper function for you to create your main window in the same exception-safe manner. Let's say you normally create your main window with `MainWindow w{ "arg1", "arg2" };`. With cavansite you can do it with `auto w = a.createMainWindow<MainWindow>("arg1", "arg2");` (assuming `a` is of type `CApplication`), passing your window type as the template parameter and constructor arguments as function arguments. This function also supports a `bool` NTTP that dictates whether or not to automatically call `show()` on the newly created window, and it _defaults to `true`_. You can disable this automatic call by passing `false` (e.g. `a.createMainWindow<MainWindow, false>();`) or explicitly pass `true`, mimicking default behavior (`a.createMainWindow<MainWindow, true>();`)

> [!IMPORTANT]
> `createMainWindow<WinT>()` returns `std::unique_ptr<WinT>`, meaning in order for your window to not be immediately deleted (due to `std::unique_ptr` being destroyed) you need to either save it to a variable (`auto w` in the example) or release the pointer from the `std::unique_ptr` object

Breeze themes initialization is handled automatically by `CApplication` if Breeze themes are enabled

---

Another initialization step _not_ handled by `CApplication` is _settings initialization_. You can read more in [SettingsManager.md](./classes/singletons/SettingsManager.md), but the main point is that in order to use settings (which is mandatory with Breeze themes) you need to input the folder name, and, possibly, other parameters you might want to customize about the file your settings will be stored in. This is done with `SettingsManager::init`

---

Finally, the exception handler cavansite uses can be set to any function you want. The function signature is `void handler(std::exception const&) noexcept`, and by calling `utils::setExceptionHandler` you can replace cavansite's default handler. To reset the handler back to the default one simply call `utils::setExceptionHandler({})`


## Extra Notes
cavansite provides logging utilities via the Aurora library. Please make sure to read through its [README](https://github.com/Fryy55/aurora/blob/main/README.md) to get familiar with all features and settings

Now that you're done with basics, check out [other](./) documentation! If some classes/utilities do not have a file for them it means their usage is rather straightforward and can be completely inferred from common sense/checking headers, and there are no special remarks to be made about them. Everything mentioned in this document will also not get a dedicated page


### Minimal Example
```c++
#include "MainWindow.hpp"

#include <cavansite/cavansite.hpp>


int main(int argc, char** argv) {
    cavansite::CApplication a{ argc, argv };

    auto w = a.createMainWindow<MainWindow>();

    return a.exec();
}
```


### Full Config Example
```c++
#include "MainWindow.hpp"

#include <cavansite/cavansite.hpp>


static void myAmazingHandler(std::exception const& exception) noexcept {
    aurora::log::error("Exception caught: {}", exception.what());

    std::exit(1);
}

int main(int argc, char** argv) {
    cavansite::utils::setExceptionHandler(myAmazingHandler);
    cavansite::SettingsManager::init("my-epic-app");


    cavansite::CApplication a{ argc, argv };

    auto w = a.createMainWindow<MainWindow>();

    return a.exec();
}
```