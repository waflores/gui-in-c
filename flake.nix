{
  description = "gui-in-c";

  # nixConfig.bash-prompt-suffix = "m4kc> ";

  inputs = {
    # keep-sorted start
    blueprint.inputs.nixpkgs.follows = "nixpkgs";
    blueprint.url = "https://github.com/numtide/blueprint/archive/7ae8756a68c662d551e354beb537f365b80e5108.tar.gz";
    nixpkgs.url = "https://github.com/NixOS/nixpkgs/archive/b107b36e150478e05bd06d50bcc4f2218df0257f.tar.gz"; # 25.05 - 2025-03-26
    treefmt-nix.inputs.nixpkgs.follows = "nixpkgs";
    treefmt-nix.url = "https://github.com/numtide/treefmt-nix/archive/adc195eef5da3606891cedf80c0d9ce2d3190808.tar.gz";
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