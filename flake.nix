{
  description = "Nix Flake for the second assignment";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }:
  let
    system = "x86_64-linux";
    pkgs = import nixpkgs { inherit system; };
  in
  {
    devShell.${system} = pkgs.mkShell {
      buildInputs = with pkgs; [
        python3
        scons
        cmake
        llvm
        pkg-config
        gcc

        # Graphical dependencies
        libGL
        libxkbcommon
        vulkan-loader
        xorg.libX11
        xorg.libXcursor
        xorg.libXext
        xorg.libXfixes
        xorg.libXi
        xorg.libXinerama
        xorg.libXrandr
        xorg.libXrender
        
        # Audio dependencies
        alsa-lib
        libpulseaudio
        pulseaudio
        
        # System services
        dbus
        fontconfig
        udev
        
        # Wayland
        wayland
        wayland-scanner
        
        # Misc
        mesa
        patchelf
        speechd
      ];

      # Required for runtime library discovery
      shellHook = ''
        export LD_LIBRARY_PATH=${
          pkgs.lib.makeLibraryPath [
            pkgs.libGL
            pkgs.libxkbcommon
            pkgs.vulkan-loader
            pkgs.alsa-lib
            pkgs.libpulseaudio
            pkgs.fontconfig
            pkgs.udev
            pkgs.xorg.libX11
            pkgs.xorg.libXcursor
            pkgs.xorg.libXext
            pkgs.xorg.libXfixes
            pkgs.xorg.libXi
            pkgs.xorg.libXinerama
            pkgs.xorg.libXrandr
            pkgs.xorg.libXrender
            pkgs.wayland
          ]
        }:$LD_LIBRARY_PATH
      '';
    };
  };
}
