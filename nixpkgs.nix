let
  lock = builtins.fromJSON (builtins.readFile ./flake.lock);
  src = lock.nodes.nixpkgs.locked;
  nixpkgs = fetchTarball {
    inherit (src) url;
    sha256 = src.narHash;
  };
in
import nixpkgs
