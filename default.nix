{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = [
    pkgs.glfw        # GLFW for window/context management
    pkgs.libGL       # OpenGL library (core OpenGL)
    pkgs.mesa        # Mesa (provides OpenGL implementation)
    pkgs.freeglut    # FreeGLUT (alternative to GLUT)
    pkgs.gcc         # GCC compiler (includes standard library support)
    pkgs.glew        # GLEW (OpenGL Extension Wrangler Library)
    pkgs.glm         # GLM (OpenGL Mathematics)
  ];

  shellHook = ''
    # Ensure proper environment setup for GCC and glibc
    export CPPFLAGS="-I${pkgs.glfw}/include -I${pkgs.glew}/include -I${pkgs.mesa}/include -I${pkgs.glm}/include"
    export LDFLAGS="-L${pkgs.glfw}/lib -L${pkgs.mesa}/lib -L${pkgs.glew}/lib"
    
    # Correct the CXXFLAGS by removing `.dev` from the GCC path
    export CXXFLAGS="-I${pkgs.gcc}/include/c++/${pkgs.gcc.version} -I${pkgs.glibc}/include"
  '';
}
