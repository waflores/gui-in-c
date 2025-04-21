# Using mkShell from nixpkgs
{
  pkgs,
  ...
}:
pkgs.mkShell.override { stdenv = pkgs.clangStdenv; } rec {
  name = "gui-shell";
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
      # keep-sorted start block=yes case=no
      (python3.withPackages (
        python-pkgs: with python-pkgs; [
          venvShellHook
        ]
      ))
      bashInteractive
      bazelisk
      compiledb
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
      SDL2
      SDL2.dev
      tree
      vim
      # keep-sorted end
    ]
    ++ xorgDeps;
}

# https://github.com/numtide/blueprint/blob/main/docs/content/guides/configuring_direnv.md
