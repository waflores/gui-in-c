{
  description = "gui-in-c";

  # nixConfig.bash-prompt-suffix = "guic> ";

  inputs = {
    # keep-sorted start
    blueprint.inputs.nixpkgs.follows = "nixpkgs";
    blueprint.url = "https://github.com/numtide/blueprint/archive/5a9bba070f801d63e2af3c9ef00b86b212429f4f.tar.gz";
    nixpkgs.url = "https://github.com/NixOS/nixpkgs/archive/2493002b10ccef0880f72d7720538f91fb4f7434.tar.gz"; # 26.05-pre  2025-11-24
    treefmt-nix.inputs.nixpkgs.follows = "nixpkgs";
    treefmt-nix.url = "https://github.com/numtide/treefmt-nix/archive/5b4ee75aeefd1e2d5a1cc43cf6ba65eba75e83e4.tar.gz";
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
