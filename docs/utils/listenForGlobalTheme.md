# listenForGlobalTheme
If you are not using Breeze themes and want an easy way to call a callback on global (system) theme change you can pass your callback to this function. There are 2 signatures - one that accepts a callback (signature `void callback(Qt::ColorScheme mode)`) and another one accepts an object pointer with a pointer to a member function of that object's type (for easy binding to member functions)

> [!NOTE]
> The reason this is redundant with Breeze themes is due to `BreezeManager` sending theme updates to interfaces by itself on global theme change

The header also defines a `CAVANSITE_GLOBAL_THEME_PARAM` macro. This macro simply creates a `Qt::ColorScheme` parameter named `mode` and defaults it to application's current color scheme (see example below). This is useful for an update function that will be called with a parameter on callback and without a parameter in the constructor

```c++
static void foo(Qt::ColorScheme mode) noexcept {
    aurora::log::debug(
        "Global theme changed! Now it's {} (in numbers)",
        std::to_underlying(mode)
    );

    return;
}

class Example final {
public:
    Example() {
        // add widgets

        this->themeChange(); // update newly created widgets to the current theme (default param)
        // optionally do `cavansite::utils::listenForGlobalTheme(this, &Example::themeChange);` here instead of somewhere else
    }

    void themeChange(CAVANSITE_GLOBAL_THEME_PARAM) {
        // update some widget stuff with the `mode` param

        return;
    }
};


// ...

cavansite::utils::listenForGlobalTheme(foo);

auto a = new Example();
cavansite::utils::listenForGlobalTheme(a, &Example::themeChange);
```