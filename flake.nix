{
  description = "gui-in-c";

  # nixConfig.bash-prompt-suffix = "guic> ";

  inputs = {
    # keep-sorted start
    blueprint.inputs.nixpkgs.follows = "nixpkgs";
    blueprint.url = "https://github.com/numtide/blueprint/archive/0ed984d51a3031065925ab08812a5434f40b93d4.tar.gz";
    nixpkgs.url = "https://github.com/NixOS/nixpkgs/archive/2493002b10ccef0880f72d7720538f91fb4f7434.tar.gz"; # 26.05-pre  2025-11-24
    treefmt-nix.inputs.nixpkgs.follows = "nixpkgs";
    treefmt-nix.url = "https://github.com/numtide/treefmt-nix/archive/e96d59dff5c0d7fddb9d113ba108f03c3ef99eca.tar.gz";
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
