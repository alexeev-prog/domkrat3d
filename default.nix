{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = [
    pkgs.glfw                               # GLFW for window/context management
    pkgs.libGL                              # OpenGL library (core OpenGL)
    pkgs.mesa                               # Mesa (provides OpenGL implementation)
    pkgs.freeglut                           # FreeGLUT (alternative to GLUT)
    pkgs.gcc                                # GCC compiler (includes standard library support)
    pkgs.glew                               # GLEW (OpenGL Extension Wrangler Library)
    pkgs.glm                                # GLM (OpenGL Mathematics)
    pkgs.cmake                              # Cmake
    pkgs.vulkan-tools                       # Khronos official Vulkan Tools and Utilities
    pkgs.vulkan-utility-libraries           # Set of utility libraries for Vulkan
    pkgs.vulkan-headers                     # Vulkan Header files and API registry
    pkgs.vulkan-validation-layers           # Official Khronos Vulkan validation layers
    pkgs.vulkan-memory-allocator            # Easy to integrate Vulkan memory allocation library
    pkgs.vulkan-loader                      # LunarG Vulkan loader
    pkgs.stb                                # Single-file public domain libraries for C/C++
    pkgs.entt                               # Header-only, tiny and easy to use library for game programming and much more written in modern C++
    pkgs.vulkan-extension-layer             # Layers providing Vulkan features when native support is unavailable
    pkgs.vulkan-cts                         # Khronos Vulkan Conformance Tests
    pkgs.sfml                               # Simple and fast multimedia library
  ];

  shellHook = ''
    # Ensure proper environment setup for GCC and glibc
    export CPPFLAGS="-I${pkgs.glfw}/include -I${pkgs.glew}/include -I${pkgs.mesa}/include -I${pkgs.glm}/include"
    export LDFLAGS="-L${pkgs.glfw}/lib -L${pkgs.mesa}/lib -L${pkgs.glew}/lib"
    
    # Correct the CXXFLAGS by removing `.dev` from the GCC path
    export CXXFLAGS="-I${pkgs.gcc}/include/c++/${pkgs.gcc.version} -I${pkgs.glibc}/include"
  '';
}
