#!/bin/bash

# Exit on error
set -e

echo "Setting up CPoll development environment for macOS..."

# Check if Homebrew is installed
if ! command -v brew &> /dev/null; then
    echo "Installing Homebrew..."
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
fi

# Install dependencies
echo "Installing dependencies..."
brew install \
    llvm \
    cppcheck \
    node \
    mingw-w64 \
    wine-stable \
    meson \
    ninja

# Add LLVM to PATH if not already present
if ! grep -q "llvm/bin" ~/.zshrc; then
    echo 'export PATH="/opt/homebrew/opt/llvm/bin:$PATH"' >> ~/.zshrc
    echo "Added LLVM to PATH in ~/.zshrc"
fi

# Install Node.js dependencies
echo "Installing Node.js dependencies..."
npm install

echo "Setup complete! Please restart your terminal or run:"
echo "source ~/.zshrc" 