{ pkgs, inputs, ... }:
inputs.treefmt-nix.lib.mkWrapper pkgs {
  # Used to find the project root
  projectRootFile = ".git/config";

  # See this for options:
  # https://github.com/numtide/treefmt-nix/tree/8d404a69efe76146368885110f29a2ca3700bee6/programs
  programs = {
    # keep-sorted start
    buildifier.enable = true;
    clang-format.enable = true;
    deadnix.enable = true;
    dos2unix.enable = true;
    keep-sorted.enable = true;
    # mdformat.enable = true;
    mdsh.enable = true;
    nixfmt.enable = true;
    nixfmt.package = pkgs.nixfmt-rfc-style;
    ruff.check = true;
    ruff.format = true;
    shellcheck.enable = true;
    shfmt.enable = true;
    statix.enable = true;
    typos.enable = true;
    yamlfmt.enable = true;
    # keep-sorted end
  };

  settings.global.excludes = [
    "LICENSE"
    # let's not mess with the test folder
    "test/*"
    # unsupported extensions
    "*.{gif,png,svg,tape,mts,lock,mod,sum,gitignore,pages}"
    ".cache/*"
    ".direnv/*"
    "bazel-*"
    "external/*"
  ];

  # settings.formatter = {
  #   shellcheck.includes = [ "direnvrc" ];
  #   shfmt.includes = [ "direnvrc" ];
  # };
}
