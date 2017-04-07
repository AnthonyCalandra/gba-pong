# gba-pong

Simple pong game on the GameBoy Advance.

![Pong screen](http://anthony-calandra.com/downloads/gba.jpg "Pong screen")

## Build instructions

devkitPro needs to be installed. Make sure you export them when running the makefile. On Mac OSX Yosemite you can add the following lines to your `~/.bash_profile`:
```bash
export DEVKITPRO=/opt/devkitPro
export DEVKITARM=/opt/devkitPro/devkitARM
```

Just run the makefile and it should generate an elf and gba file in the bin directory. You can run the gba file through an emulator or use it to play on the actual GameBoy Advance hardware.

## Technical Details

- Bitmap-based in mode 4.
- Uses the GBA's page flipping capabilities.
- Uses a CpuFastSet implementation for fast page clearing.
- Basic font system.

## Author

Anthony Calandra

## License

MIT
