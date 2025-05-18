# Building with CMake

## Dependencies
Install this dependencies to build domkrat3d:

| Library                  | Purpose                                   | Explanation                                                                                |
|-------------------------|-------------------------------------------|------------------------------------------------------------------------------------------|
| **glfw**                | Window and Context Management             | Creates OS windows and handles input devices, essential for OpenGL context creation.     |
| **libGL**               | OpenGL Core Library                       | Provides OpenGL functionality, especially useful when a fallback is needed.              |
| **libGLU**              | OpenGL Utility Library                    | Provides additional functionalities for OpenGL, such as simplifying matrix and primitive operations. |
| **mesa**                | OpenGL Implementation                     | Useful for development and testing on OpenGL, especially on systems without hardware acceleration. |
| **glew**                | OpenGL Extension Wrangler                 | Helps manage OpenGL extensions, particularly important for compatibility.                 |
| **glm**                 | Math Library                             | Offers specialized vector and matrix operations optimized for graphics.                  |
| **stb**                 | Utility C Libraries for Images and Fonts | Popular single-header libraries for loading and working with images.                      |
| **entt**                | Entity-Component-System Library          | A lightweight and efficient ECS implementation for managing game entities.               |
| **cmake**               | Build System                             | The most widely used tool for cross-platform project build configuration.                |
| **gcc**                 | C++ Compiler                             | Required to build the engine and projects, providing numerous options and standard support. |
| **clang**               | Compiler and Code Analysis Tools          | A highly efficient compiler with powerful code analysis and diagnostics capabilities.      |
| **clang-tidy-sarif**   | Static Code Analysis Tool                 | Performs static code analysis to find potential errors before running the program.       |
| **clang-tools**         | Tools for Working with Clang              | A suite of tools aimed at improving code quality and automating development processes.   |
| **imgui**               | Immediate Mode GUI Library               | A simple yet powerful library for creating graphical user interfaces in applications.    |
| **freeglut**           | Alternative for Window and Input Handling  | A lightweight alternative for managing windows and input, often used in demo projects. |
| **portaudio**          | Audio Library                            | Provides user-friendly interfaces for working with audio devices.                         |
| **valgrind**           | Performance Analysis Tool                | Used for detecting memory leaks and profiling performance.                                |
| **gdb**                 | Debugger                                  | A tool for debugging programs, allowing the analysis of execution and error finding.     |
| **apitrace**           | API Tracing Tool                         | Enables tracking API calls in OpenGL, useful for debugging and performance analysis.     |
| **glava**              | OpenGL Performance Testing                | A utility designed for testing OpenGL performance and frame analysis.                    |
| **glui**               | GUI Library for OpenGL                   | Provides a set of tools for creating graphical user interfaces based on OpenGL.          |
| **glmark2**            | Performance Benchmark                     | Evaluates the performance of a system based on OpenGL, well-suited for graphics testing. |
| **glpng**              | PNG Library                               | Allows loading and processing PNG formatted images in graphics applications.               |
| **vulkan**             | Vulkan Library                            | Allows work with Vulkan API                                                                 |
| **validation layers** | Vulkan Layers Validations                  | Allow validations layers from Vulkan SDK LunarG                                             |

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
