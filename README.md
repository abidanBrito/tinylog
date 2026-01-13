# Tinylog

[![STATUS](https://img.shields.io/badge/status-WIP-red.svg)](https://github.com/abidanBrito/tinylog)

A minimal and thread-safe header-only logging library with zero dependencies.

## Features
- [x] Multiple log levels (TRACE, DEBUG, INFO, WARN, ERROR, FATAL).
- [x] Colored console output (ANSI color codes).
- [x] Thread-safe synchronous logger.
- [x] Type-safe formatting.
- [x] Console sink.
- [x] File sink.
- [ ] Network sink (TCP/UDP).
- [ ] Asynchronous logger with background thread.
- [ ] Custom output formatters.
- [ ] Custom timestamp formats (ISO8601, RFC3339, etc.).
- [ ] Multiple simultaneous sinks.
- [ ] Log rotation (size-based and time-based).
- [x] Log level from environment variable
- [ ] Source locations macros (file:line).
- [ ] Structured logging (JSON).
- [ ] Filter by regex/pattern.
- [ ] Context tags.

## Quick Start
```cpp
#include <tinylog/sync_logger.hpp>

auto main() -> int
{
    tinylog::SyncLogger logger(tinylog::LogLevel::TRACE);

    logger.trace("Application starting...");
    logger.debug("Loading configuration file from config.yaml...");
    logger.info("Server listening on port 8080");
    logger.warn("Cache is 80% full");
    logger.error("Failed to connect to database");
    logger.fatal("Out of memory!");

    return 0;
}
```

![Console_Logging_Example](/img/console_logging.png)

See [examples/](examples/) for formatted strings, dynamic log levels, multithreading and more.

## Installation
### CMake (recommended)
#### Automatic download
```cmake
include(FetchContent)
FetchContent_Declare(
    tinylog
    GIT_REPOSITORY https://github.com/abidanBrito/tinylog
    GIT_TAG main
)
FetchContent_MakeAvailable(tinylog)

target_link_libraries(your_target PRIVATE tinylog::tinylog)
```

#### Manual integration
Copy the `include/tinylog/` directory to your project, either manually or by running one of the commands below:

**Linux/macOS**
```bash
cp -r include/tinylog /path/to/your/project/include/
```

**Windows (Command Prompt)**
```cmd
xcopy /E /I include\tinylog \path\to\your\project\include\tinylog
```

**Windows (PowerShell)**
```powershell
Copy-Item -Path "include\tinylog" -Destination "\path\to\your\project\include\tinylog" -Recurse
```

Then add this to your CMakeLists.txt in order to link against tinylog:
```cmake
add_subdirectory(path/to/tinylog)
target_link_libraries(your_target PRIVATE tinylog::tinylog)
```

### Without CMake
Simply copy the `include/tinylog/` directory to your project and compile with C++20 and link `pthread`.

**GCC**
```bash
g++ -std=c++20 -pthread -I./include main.cpp -o app
```

**Clang**
```bash
clang++ -std=c++20 -pthread -I./include main.cpp -o app
```

**MSVC**
```cmd
cl /std:c++20 /EHsc /I.\include main.cpp
```

## LICENSE
This repository is released under the MIT license. See [LICENSE](LICENSE) for more information.
