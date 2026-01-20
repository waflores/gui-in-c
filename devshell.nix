# Using mkShell from nixpkgs
{
  pkgs,
  ...
}:
pkgs.mkShell.override
  {
    # stdenv = pkgs.clangStdenv;
  }
  rec {
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
        bazel-buildtools
        bazelisk
        cacert
        clang
        clang-tools
        clang-uml
        compiledb
        dbus
        dbus.lib
        direnv
        fzf
        gdb
        git
        glib
        glib.dev
        glib.out
        gtk4
        gtk4.dev
        gzip
        jdk8
        libdrm
        libglvnd
        libglvnd.dev
        libxkbcommon
        massif-visualizer
        mesa
        mesa-demos
        mesa.spirv2dxil
        ninja
        nix
        nix-output-monitor
        pkg-config
        plantuml-c4
        # # this is for the shellhook portion
        # qt6.wrapQtAppsHook
        sdl3
        sdl3.dev
        tree
        valgrind
        vim
        zlib
        zlib.dev
        # keep-sorted end
      ]
      ++ xorgDeps;
  }

# https://github.com/numtide/blueprint/blob/main/docs/content/guides/configuring_direnv.md
