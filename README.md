# CPoll

A simple asynchronous polling system for C. This is an experimental project to explore C programming capabilities.

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

#### Windows Cross-Compilation
Available on macOS and Linux. Requires MinGW-w64 and Wine:

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

# Run Windows tests (requires Wine)
meson test -C builddir-windows --wrapper wine64
```

## Status

Experimental project - not ready for production use.

