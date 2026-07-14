# Exceptions
With the exception handling system cavansite provides there are custom exceptions. Aside from exception classes already provided (the generic `Exception`, `InterfaceException`, etc.) cavansite gives you an easy way to create your own fully compatible exception types in just one line of code. `Exception.hpp` defines a `CAVANSITE_REGISTER_EXCEPTION` macro, that creates an exception class in the current namespace. This exception automatically logs itself with a `[cavansite]` prefix on error level once it's thrown and has a `className()` method that returns its class name, as well as the standard `what()` method for exception information

```c++
#pragma once

#include <cavansite/utils/except/Exception.hpp>


namespace foo { CAVANSITE_REGISTER_EXCEPTION(MyCoolException); }
```

To catch strictly cavansite exceptions you can catch based on `cavansite::except::ExceptionType`. It is an interface that exposes `what()` and `className()` and what all exceptions created with the macro inherit. _Make sure to catch a `const&` since `ExceptionType` is abstract_

```c++
catch (cavansite::except::ExceptionType const& exception) {
    aurora::log::error(
        "Caught {} with a message '{}'",
        exception.className(), exception.what()
    );
}
```