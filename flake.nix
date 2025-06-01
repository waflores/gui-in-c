{
  description = "gui-in-c";

  # nixConfig.bash-prompt-suffix = "m4kc> ";

  inputs = {
    # keep-sorted start
    blueprint.inputs.nixpkgs.follows = "nixpkgs";
    blueprint.url = "https://github.com/numtide/blueprint/archive/49bbd5d072b577072f4a1d07d4b0621ecce768af.tar.gz";
    nixpkgs.url = "https://github.com/NixOS/nixpkgs/archive/5cfaab2c5c1492cbec3e5e85a4dca8601858a06a.tar.gz"; # 25.05 - 2025-04-24
    treefmt-nix.inputs.nixpkgs.follows = "nixpkgs";
    treefmt-nix.url = "https://github.com/numtide/treefmt-nix/archive/8d404a69efe76146368885110f29a2ca3700bee6.tar.gz";
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
