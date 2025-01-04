#!/bin/bash

# Exit on error
set -e

echo "Building and testing for Windows..."

# Setup Windows build directory
meson setup builddir-windows --cross-file windows.ini

# Build
ninja -C builddir-windows

# Run tests
echo "Running tests..."
cd builddir-windows

echo "Running poll test..."
WINEPATH="$(pwd)/src" wine64 tests/test_poll.exe

echo "Running async test..."
WINEPATH="$(pwd)/src" wine64 tests/test_async.exe

echo "Running ucontext test (should be skipped)..."
WINEPATH="$(pwd)/src" wine64 tests/test_ucontext.exe 
