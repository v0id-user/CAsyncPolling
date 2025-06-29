# CAsyncPolling

A lightweight, asynchronous polling system implemented in C. This experimental project aims to explore my capabilities in C programming while delving into the inner workings of asynchronous mechanisms.
<div align="center">

[![MADE BY #V0ID](https://img.shields.io/badge/MADE%20BY%20%23V0ID-F3EEE1.svg?style=for-the-badge)](https://github.com/v0id-user)

</div>
# (1/4/2025) Current Status

The project is almost reach stable state in [test_async.c](tests/test_async.c). You can compile the test(WINDOWS ONLY) and it will run probably, but it's not memory safe and there is memory leaks everywhere and it's not tested very well, but the concept is there.

## Setup Instructions

### Automatic Setup

#### macOS
```bash
./scripts/setup_macos.sh  # Installs all dependencies
meson setup builddir
ninja -C builddir
```

#### Linux (Ubuntu/Debian)
```bash
./scripts/setup_linux.sh  # Installs all dependencies
meson setup builddir
ninja -C builddir
```

### Manual Setup

#### macOS
```bash
# Install dependencies
brew install llvm cppcheck node mingw-w64 wine-stable meson ninja

# Add LLVM to PATH (add to ~/.zshrc)
export PATH="/opt/homebrew/opt/llvm/bin:$PATH"

# Build
meson setup builddir
ninja -C builddir
```

#### Linux (Ubuntu/Debian)
```bash
# Install dependencies
sudo apt-get update
sudo apt-get install -y clang clang-format cppcheck nodejs npm python3-pip ninja-build
pip3 install --user meson

# Build
meson setup builddir
ninja -C builddir
```

#### Windows
Using [MSYS2](https://www.msys2.org/):
```bash
# Install MSYS2 from https://www.msys2.org/

# Open MSYS2 UCRT64 and install dependencies
pacman -Syu
pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-meson mingw-w64-ucrt-x86_64-ninja

# Build
meson setup builddir
ninja -C builddir
```

Using Visual Studio (2019 or later):
```powershell
# Install dependencies
winget install Python.Python
winget install Ninja-build.Ninja
pip install meson

# Open "Developer Command Prompt for VS" and build
meson setup builddir
ninja -C builddir
```

### Cross-Compilation
#### Building Windows version on macOS/Linux
Requires MinGW-w64 and Wine:

```bash
# Build for Windows
meson setup builddir-windows --cross-file windows.ini
ninja -C builddir-windows

# Run tests (requires Wine)
cd builddir-windows
WINEPATH="$(pwd)/src" wine64 tests/test_poll.exe
```

## Running Tests

```bash
# Run all tests
meson test -C builddir

# Run Windows cross-compiled tests (requires Wine)
meson test -C builddir-windows --wrapper wine64
```

## Status

Experimental project - not ready for production use.

