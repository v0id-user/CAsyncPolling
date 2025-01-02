#!/bin/bash

# Exit on error
set -e

echo "Setting up CPoll development environment for Linux..."

# Install dependencies
echo "Installing dependencies..."
sudo apt-get update
sudo apt-get install -y \
    clang \
    clang-format \
    cppcheck \
    nodejs \
    npm \
    gcc-mingw-w64-x86-64 \
    g++-mingw-w64-x86-64 \
    wine64 \
    python3-pip \
    ninja-build

# Install Meson
pip3 install --user meson

# Install Node.js dependencies
echo "Installing Node.js dependencies..."
npm install

echo "Setup complete!" 