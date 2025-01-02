# CPoll

CPoll is a simple asynchronous polling system for C. It is designed to be easy to use, understand and as an experiment to see how much I can do in C.

## Prerequisites

- A C compiler (gcc, clang)
- [Meson](https://mesonbuild.com/) build system
- [Ninja](https://ninja-build.org/) build tool

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

