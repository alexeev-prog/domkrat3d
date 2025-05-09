# Building with CMake

## Dependencies
Install this dependencies to build domkrat3d:

```bash
glfw                               # GLFW for window/context management
libGL                              # OpenGL library (core OpenGL)
mesa                               # Mesa (provides OpenGL implementation)
freeglut                           # FreeGLUT (alternative to GLUT)
gcc                                # GCC compiler (includes standard library support)
glew                               # GLEW (OpenGL Extension Wrangler Library)
glm                                # GLM (OpenGL Mathematics)
cmake                              # Cmake
vulkan-tools                       # Khronos official Vulkan Tools and Utilities
vulkan-utility-libraries           # Set of utility libraries for Vulkan
vulkan-headers                     # Vulkan Header files and API registry
vulkan-validation-layers           # Official Khronos Vulkan validation layers
vulkan-memory-allocator            # Easy to integrate Vulkan memory allocation library
vulkan-loader                      # LunarG Vulkan loader
stb                                # Single-file public domain libraries for C/C++
entt                               # Header-only, tiny and easy to use library for game programming and much more written in modern C++
vulkan-extension-layer             # Layers providing Vulkan features when native support is unavailable
vulkan-cts                         # Khronos Vulkan Conformance Tests
sfml                               # Simple and fast multimedia library
boost                              # Basic C++ Libraries
clang                              # Clang tools
clang-tools                        # Clang tools (clangd, etc)
pkg-config                         # Package config
gdb                                # GNU Debugger
valgrind                           # Find memory leaks and other typical C++ errors
```

Or, if use NixOS, you would can start nix-shell:

```bash
nix-shell .
```

## Build

 > You can use our [build-script](./build.sh) (if use linux): `./build.sh`

This project doesn't require any special command-line flags to build to keep
things simple.

Here are the steps for building in release mode with a single-configuration
generator, like the Unix Makefiles one:

```sh
cmake -S . -B build -D CMAKE_BUILD_TYPE=Release
cmake --build build
```

Here are the steps for building in release mode with a multi-configuration
generator, like the Visual Studio ones:

```sh
cmake -S . -B build
cmake --build build --config Release
```

### Building with MSVC

Note that MSVC by default is not standards compliant and you need to pass some
flags to make it behave properly. See the `flags-msvc` preset in the
[CMakePresets.json](CMakePresets.json) file for the flags and with what
variable to provide them to CMake during configuration.

### Building on Apple Silicon

CMake supports building on Apple Silicon properly since 3.20.1. Make sure you
have the [latest version][1] installed.

## Install

This project doesn't require any special command-line flags to install to keep
things simple. As a prerequisite, the project has to be built with the above
commands already.

The below commands require at least CMake 3.15 to run, because that is the
version in which [Install a Project][2] was added.

Here is the command for installing the release mode artifacts with a
single-configuration generator, like the Unix Makefiles one:

```sh
cmake --install build
```

Here is the command for installing the release mode artifacts with a
multi-configuration generator, like the Visual Studio ones:

```sh
cmake --install build --config Release
```

### CMake package

This project exports a CMake package to be used with the [`find_package`][3]
command of CMake:

* Package name: `domkrat3d`
* Target name: `domkrat3d::domkrat3d`

Example usage:

```cmake
find_package(domkrat3d REQUIRED)
# Declare the imported target as a build requirement using PRIVATE, where
# project_target is a target created in the consuming project
target_link_libraries(
    project_target PRIVATE
    domkrat3d::domkrat3d
)
```

### Note to packagers

The `CMAKE_INSTALL_INCLUDEDIR` is set to a path other than just `include` if
the project is configured as a top level project to avoid indirectly including
other libraries when installed to a common prefix. Please review the
[install-rules.cmake](cmake/install-rules.cmake) file for the full set of
install rules.

[1]: https://cmake.org/download/
[2]: https://cmake.org/cmake/help/latest/manual/cmake.1.html#install-a-project
[3]: https://cmake.org/cmake/help/latest/command/find_package.html
