{ pkgs ? import <nixpkgs> {} }:
let
  libs = with pkgs; [
  	boost
    cmake
    glfw
    clang
    clang-tools
    clang-tidy-sarif
    glew
    clang-analyzer
    libclang
    stb
    entt
    glm
    gcc
    pkg-config
    gdb
    mesa
    vulkan-volk
    vulkan-tools
    vulkan-loader
    vulkan-headers
    vulkan-validation-layers
    vulkan-tools-lunarg
    vulkan-extension-layer
  ];
  lib = libs;
in
pkgs.mkShell {
  nativeBuildInputs = with pkgs; [
    (vscode-with-extensions.override {
      vscodeExtensions = with vscode-extensions; [
      	jdinhlife.gruvbox
        ms-vscode.cpptools
        ms-vscode.cpptools-extension-pack
        llvm-vs-code-extensions.vscode-clangd
      ];
    })
    cppcheck
    clang-tools
    codespell
    conan
    doxygen
    gtest
    lcov
    vcpkg
    vcpkg-tool
  ];

  buildInputs = libs;
  LD_LIBRARY_PATH = pkgs.lib.makeLibraryPath libs;
  VK_LAYER_PATH = "${pkgs.vulkan-validation-layers}/share/vulkan/explicit_layer.d";
  VULKAN_SDK = "${pkgs.vulkan-validation-layers}/share/vulkan/explicit_layer.d";
  # XDG_DATA_DIRS = builtins.getEnv "XDG_DATA_DIRS";
  # XDG_RUNTIME_DIRS = "/run/user/1001/";
  shellHook = ''
    echo "domkrat3d C++ Vulkan Dev Shell"
    # Ensure proper environment setup for GCC and glibc
    export CPPFLAGS="-I${pkgs.glfw}/include -I${pkgs.glew}/include -I${pkgs.mesa}/include -I${pkgs.glm}/include -I${pkgs.vulkan-headers}"
    export LDFLAGS="-L${pkgs.glfw}/lib -L${pkgs.mesa}/lib -L${pkgs.glew}/lib"
    
    # Correct the CXXFLAGS by removing `.dev` from the GCC path
    export CXXFLAGS="-I${pkgs.gcc}/include/c++/${pkgs.gcc.version} -I${pkgs.glibc}/include"

	export LIBRARY_PATH=${pkgs.glfw}/lib:${pkgs.vulkan-loader}/lib:$LIBRARY_PATH
    export CPATH=${pkgs.glfw}/include:${pkgs.vulkan-headers}/include:$CPATH
    export VK_ICD_FILENAMES=${pkgs.vulkan-loader}/etc/vulkan/icd.d/nvidia_icd.json
    export VK_LAYER_PATH=${pkgs.vulkan-validation-layers}/etc/vulkan/explicit_layer.d
  '';
}

