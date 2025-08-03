{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = with pkgs; [
    clang
    clang-tools
    cmake
    ninja
    pkg-config
    gcc
    conan
    vcpkg

    libxkbcommon
    xorg.libX11
    xorg.libXcursor
    xorg.libXrandr
    xorg.libXi

    vulkan-headers
    vulkan-loader
    vulkan-tools
    vulkan-validation-layers
    vulkan-extension-layer
    glfw
    glew
    glm
    stb
    imgui
    entt
    freeglut
    libGLU
    mesa

    portaudio
    SDL2
    SDL2_mixer

    gdb
    valgrind
    cppcheck
    codespell
    doxygen
    gtest
    lcov
  ];

  LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath [
    pkgs.vulkan-loader
    pkgs.glfw
    pkgs.glew
    pkgs.mesa
    pkgs.SDL2
  ];

  VK_LAYER_PATH = "${pkgs.vulkan-validation-layers}/share/vulkan/explicit_layer.d";
  
  shellHook = ''
    echo "Vulkan/OpenGL Game Engine Development Shell"
    export CC=clang
    export CXX=clang++
  '';
}
