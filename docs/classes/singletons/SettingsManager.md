# SettingsManager
`SettingsManager` is a singleton that manages all settings for your application

In order to start using it you need to first _initialize_ it with a `SettingsManager::init` function. You _must_ at least supply a directory name for your settings file, but can also optionally provide a filename (defaults to "settings"), format (defaults to `.ini`) and scope (defaults to user-wide settings)

Before directly using settings you might want to add _default settings_ for some keys. This allows you to have specific values that will be pulled if your current settings miss an already saved value on read. To do this, you have 2 functions: `addDefaultSetting` and `addDefaultSettings`. The first one takes a _key_ (string) and a _value_ (`QVariant`) - the key of a setting to add a default value to and the default value itself. The second one takes a vector-convertible array of these key-value pairs and batch-adds them. Usually, if you're providing an rvalue array (like in the example below) you will need to specify its type (`SettingsManager::DefaultSettings`) for CTAD

```c++
SettingsManager::get()->addDefaultSettings(
    SettingsManager::DefaultSettings{
        { "window/size", QSize{ 800, 600 } },
        { "window/fullscreen", true }
    }
);
```

> [!IMPORTANT]
> Default settings aren't preserved between startups so make sure to call `addDefaultSetting(s)` every time on application startup

For reading and writing settings there are 2 types of functions: standard (`read`/`write`) and with a default setting check (`readForceDefault`/`writeForceDefault`). The object being _written_ is `QVariant`, however, the object being returned while _reading_ is `SettingsManager::Setting`, which contains the actual value (`QVariant`) and a source for that setting, which could be `Read` (if the value was read from a previously saved setting), `DefaultProvided` (if the setting doesn't have a manually saved value and instead was pulled from _default settings_) and `DefaultConstructed` (if the setting wasn't previously saved and doesn't have a default value, so it has a default-constructed `QVariant`; impossible to get from `readForceDefault`). `read`/`write` functions read and write the setting of a specific key no matter what; `forceDefault` versions _require_ the provided key to have a default setting saved. This is made to easily catch misspellings and it's recommended for you to use `forceDefault` versions for this reason. These functions also have a boolean NTTP that defaults to `true` and dictates whether they will throw if the key is missing or not. Setting it to `false` changes the return type of `readForceDefault` from `Setting` to `std::optional<Setting>` and return type of `writeForceDefault` from `void` to `bool` and guarantees `noexcept`-ness

The last function that this class provides is `forceSyncWithDisk`, which forcibly syncs the current settings state with the file on the disk. This also automatically happens on singleton destruction during application teardown