{
  description = "gui-in-c";

  # nixConfig.bash-prompt-suffix = "guic> ";

  inputs = {
    # keep-sorted start
    blueprint.inputs.nixpkgs.follows = "nixpkgs";
    blueprint.url = "https://github.com/numtide/blueprint/archive/3c8bf84e28df2be19cc6623cb3ceeb6fc0839b91.tar.gz";
    nixpkgs.url = "https://github.com/NixOS/nixpkgs/archive/a0959a7457327eb5a98c222d5962ff95c6a3fe3e.tar.gz"; # 25.11 - 2025-09-19
    treefmt-nix.inputs.nixpkgs.follows = "nixpkgs";
    treefmt-nix.url = "https://github.com/numtide/treefmt-nix/archive/128222dc911b8e2e18939537bed1762b7f3a04aa.tar.gz";
    # keep-sorted end
  }; # End inputs

  outputs =
    inputs:
    inputs.blueprint {
      inherit inputs;
      systems = [ "x86_64-linux" ];
      nixpkgs.config.allowUnfreePredicate =
        pkg: builtins.elem (inputs.nixpkgs.lib.getName pkg) [ "vscode" ];
    };
}
