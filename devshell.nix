# Using mkShell from nixpkgs
{
  pkgs,
  ...
}:
pkgs.mkShell.override { stdenv = pkgs.clangStdenv; } rec {
  name = "m4kc-shell";
  xorgDeps = with pkgs.xorg; [
      libX11
      libXrender
      libXrandr
      libxcb
      libXmu
      libpthreadstubs
      libXext
      libXdmcp
      libXxf86vm
      libXinerama
      libSM
      libXv
      libXaw
      libXi
      libXcursor
      libXcomposite
      libXfixes
      libXtst
      libXScrnSaver
      libICE
      libXt
  ];
  packages = with pkgs; [
    # keep-sorted start
    bashInteractive
    clang
    clang-tools
    direnv
    fzf
    gzip
    jdk8
    ninja
    nix-output-monitor
    pkg-config
    SDL2
    SDL2.dev
    tree
    vim
    libdrm
    mesa
    mesa.spirv2dxil
    mesa-demos
    # keep-sorted end
  ] ++ xorgDeps;
}

# https://github.com/numtide/blueprint/blob/main/docs/content/guides/configuring_direnv.md