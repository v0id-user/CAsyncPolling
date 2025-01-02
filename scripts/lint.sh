#!/bin/bash

# Exit on error
set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

# Check for required tools
check_command() {
    if ! command -v $1 &> /dev/null; then
        echo -e "${RED}Error: $1 is not installed or not in PATH${NC}"
        echo "Please check the README.md for installation instructions"
        exit 1
    fi
}

# Find clang-format, checking multiple possible locations
find_clang_format() {
    if command -v clang-format &> /dev/null; then
        echo "clang-format"
    elif [ -f "/opt/homebrew/opt/llvm/bin/clang-format" ]; then
        echo "/opt/homebrew/opt/llvm/bin/clang-format"
    elif [ -f "/usr/local/opt/llvm/bin/clang-format" ]; then
        echo "/usr/local/opt/llvm/bin/clang-format"
    else
        echo -e "${RED}Error: clang-format not found${NC}"
        echo "Please install clang-format following the instructions in README.md"
        exit 1
    fi
}

echo "Checking for required tools..."
check_command "cppcheck"
CLANG_FORMAT=$(find_clang_format)

echo "Running C linters..."

# Run clang-format on all C files
echo "Running clang-format..."
find . -type f \( -name "*.c" -o -name "*.h" \) -not -path "./builddir/*" -exec $CLANG_FORMAT -i {} +

# Run cppcheck
echo "Running cppcheck..."
cppcheck --enable=all \
    --suppress=missingIncludeSystem \
    --error-exitcode=1 \
    --inline-suppr \
    -I include \
    --suppress=unknownMacro \
    src/ tests/

echo -e "${GREEN}All linting checks passed!${NC}" 