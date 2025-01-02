# CPoll

CPoll is a simple asynchronous polling system for C. It is designed to be easy to use, understand and as an experiment to see how much I can do in C.

## Prerequisites

- A C compiler (gcc, clang)
- [Meson](https://mesonbuild.com/) build system
- For development:
  - [clang-format](https://clang.llvm.org/docs/ClangFormat.html) for code formatting
  - [cppcheck](http://cppcheck.sourceforge.net/) for static analysis
  - [Node.js](https://nodejs.org/) for development tools

### Installing Development Dependencies

#### macOS
```bash
# Install required tools
brew install llvm cppcheck node

# Add LLVM tools to your PATH (add this to your ~/.zshrc or ~/.bash_profile)
export PATH="/opt/homebrew/opt/llvm/bin:$PATH"
```

#### Ubuntu/Debian
```bash
sudo apt-get install clang-format cppcheck nodejs npm
```

#### Windows
```bash
# Using chocolatey
choco install llvm cppcheck nodejs

# Or using winget
winget install LLVM.LLVM
winget install cppcheck.cppcheck
winget install OpenJS.NodeJS

# Make sure to add LLVM to your PATH if not done automatically
```

## Building

1. Clone the repository:
```bash
git clone https://github.com/v0id-user/cpoll.git
cd cpoll
```

2. Setup the build directory:
```bash
meson setup builddir
```

3. Compile the project:
```bash
cd builddir
meson compile
```

## Development

### Code Style and Linting

The project uses:
- clang-format for code formatting
- cppcheck for static analysis
- husky for git hooks
- commitlint for commit message conventions

After cloning the repository, install the development dependencies:
```bash
npm install
```

This will set up husky git hooks that automatically run linting before each commit.

To manually run linting:
```bash
npm run lint
```

### Commit Message Convention

We follow the [Conventional Commits](https://www.conventionalcommits.org/) specification. Each commit message should be structured as follows:

```
<type>[optional scope]: <description>

[optional body]

[optional footer(s)]
```

Types:
- `feat`: A new feature
- `fix`: A bug fix
- `docs`: Documentation only changes
- `style`: Changes that do not affect the meaning of the code
- `refactor`: A code change that neither fixes a bug nor adds a feature
- `perf`: A code change that improves performance
- `test`: Adding missing tests or correcting existing tests
- `build`: Changes that affect the build system or external dependencies
- `ci`: Changes to our CI configuration files and scripts
- `chore`: Other changes that don't modify src or test files

Examples:
```
feat: add new polling mechanism
fix(memory): resolve memory leak in async handler
chore: update development dependencies
```

## Running Tests

From the build directory:
```bash
meson test
```

Or from the project root:
```bash
cd builddir && meson test
```

## Development Status

Still in development - not ready for any use.

