# shell.nix
{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = [ pkgs.glfw pkgs.libGL pkgs.mesa pkgs.freeglut pkgs.cmake ];
}
