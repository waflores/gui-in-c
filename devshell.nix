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
  packages =
    with pkgs;
    [
      # keep-sorted start
      SDL2
      SDL2.dev
      bashInteractive
      clang
      clang-tools
      direnv
      fzf
      gzip
      jdk8
      libdrm
      mesa
      mesa-demos
      mesa.spirv2dxil
      ninja
      nix-output-monitor
      pkg-config
      tree
      vim
      # keep-sorted end
    ]
    ++ xorgDeps;
}

# https://github.com/numtide/blueprint/blob/main/docs/content/guides/configuring_direnv.md
