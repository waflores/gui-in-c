{
  description = "gui-in-c";

  # nixConfig.bash-prompt-suffix = "guic> ";

  inputs = {
    # keep-sorted start
    blueprint.inputs.nixpkgs.follows = "nixpkgs";
    blueprint.url = "https://github.com/numtide/blueprint/archive/3c8bf84e28df2be19cc6623cb3ceeb6fc0839b91.tar.gz";
    nixpkgs.url = "https://github.com/NixOS/nixpkgs/archive/934c891d823f663fdb259ce6060a4fa410f76d65.tar.gz"; # 25.05 - 2025-08-29
    treefmt-nix.inputs.nixpkgs.follows = "nixpkgs";
    treefmt-nix.url = "https://github.com/numtide/treefmt-nix/archive/74e1a52d5bd9430312f8d1b8b0354c92c17453e5.tar.gz";
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
