{
  description = "gui-in-c";

  # nixConfig.bash-prompt-suffix = "guic> ";

  inputs = {
    # keep-sorted start
    blueprint.inputs.nixpkgs.follows = "nixpkgs";
    blueprint.url = "https://github.com/numtide/blueprint/archive/49bbd5d072b577072f4a1d07d4b0621ecce768af.tar.gz";
    nixpkgs.url = "https://github.com/NixOS/nixpkgs/archive/6a81635e2691ef3587310b06d32bf3c2b26042c7.tar.gz"; # 25.05 - 2025-06-01
    treefmt-nix.inputs.nixpkgs.follows = "nixpkgs";
    treefmt-nix.url = "https://github.com/numtide/treefmt-nix/archive/1f3f7b784643d488ba4bf315638b2b0a4c5fb007.tar.gz";
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
