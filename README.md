# MSDOS-Game-Example

This is an example of a setup for building an MS-DOS game in modern Linux/Mac/Windows with some automation in DOSBox. There's no actual game in this repo but this is a good starting template for a project.

## Playing

1. Install [DOSBox](https://www.dosbox.com/)
2. Run `dist/FIREDUDE.EXE` inside DOSBox

## Development

This has only been tested on Linux; this should work on Mac if `dosbox` is added to `$PATH`.

### Setup

1. Download [Turbo C 2.01](https://cc.embarcadero.com/item/25636)
1. Extract the Turbo C files into `tools/TC`, so `tools/TC/TCC.EXE` is present
1. Download [Turbo Assembler 5.0](http://trimtab.ca/2010/tech/tasm-5-intel-8086-turbo-assembler-download/)
1. Extract `tasm/BIN/TASM.EXE` to `tools/TASM/TASM.EXE`
1. Install [DOSBox](https://www.dosbox.com/)
1. Ensure `dosbox` is in your PATH
1. (Optional) Install [EditorConfig](https://editorconfig.org) plugin - most critically, the `.editorconfig` files enforce line endings in `./src`.

### Build / Run

```bash
./build.sh && ./run.sh
```

### Caveats

Turbo C uses an old C version and runs on DOS, so ensure that:

-   All comments are block comments (`/* ... */`)
-   All source files (inside `src`) use Windows line endings (CRLF)
-   All variables are declared at the beginning of scope blocks

If you use inline assembly code, Turbo Assembler won't support the `asm { ... }` syntax:

```c
/* Doesn't work! */
void interrupt scan_keyboard(void)
{
    asm {
        cli
        ...
        sti
    }
}
```

Instead, use the `asm` keyword on each line:

```c
/* Works! */
void interrupt scan_keyboard(void)
{
    asm cli
    ...
    asm sti
}
```

### Turbo C 2.01 Compiler Help

```
Turbo C  Version 2.01  Copyright (c) 1987, 1988 Borland International
Syntax is: TCC [ options ] file[s]       * = default; -x- = turn switch x off
  -1      80186/286 Instructions          -A      Disable non-ANSI extensions
  -B      Compile via assembly            -C      Allow nested comments
  -Dxxx   Define macro                    -Exxx   Alternate assembler name
  -G      Generate for speed              -Ixxx   Include files directory
  -K      Default char is unsigned        -Lxxx   Libraries directory
  -M      Generate link map               -N      Check stack overflow
  -O      Optimize jumps                  -S      Produce assembly output
  -Uxxx   Undefine macro                  -Z      Optimize register usage
  -a      Generate word alignment         -c      Compile only
  -d      Merge duplicate strings         -exxx   Executable file name
  -f    * Floating point emulator         -f87    8087 floating point
  -gN     Stop after N warnings           -iN     Maximum identifier length N
  -jN     Stop after N errors             -k      Standard stack frame
  -lx     Pass option x to linker         -mc     Compact Model
  -mh     Huge Model                      -ml     Large Model
  -mm     Medium Model                    -ms   * Small Model
  -mt     Tiny Model                      -nxxx   Output file directory
  -oxxx   Object file name                -p      Pascal calls
  -r    * Register variables              -u    * Underscores on externs
  -v      Source level debugging          -w      Enable all warnings
  -wxxx   Enable warning xxx              -w-xxx  Disable warning xxx
  -y      Produce line number info        -zxxx   Set segment names
```

### Resources

These are some excellent resources for MS-DOS development:

#### MS-DOS game programming

| Author               | Resource                                                                                                                        |
| -------------------- | ------------------------------------------------------------------------------------------------------------------------------- |
| Alex Russell         | [Alex Russell's Dos Game Programming in C for Beginners](http://www3.telus.net/alexander_russell/course/introduction.htm)       |
| GameBub              | [C++ Graphics: MS-DOS Games](https://dos.gamebub.com/cpp.php)                                                                   |
| David Brackeen       | [256-Color VGA Programming in C](http://www.brackeen.com/vga/index.html)                                                        |
| Dr. William T. Verts | [The VGA and 256 Colors](https://people.cs.umass.edu/~verts/cs32/vga_320.html)                                                  |
| Ben Lunt             | [DOS Programming, Undocumented DOS, and DOS Secrets](http://www.fysnet.net/)                                                    |
| Mark Feldman         | [Programming the Keyboard](http://www.intel-assembler.it/portale/5/keyboard-programming-in-asm/keyboard-programming-in-asm.asp) |

#### Turbo C

| Author         | Resource                                                                                                              |
| -------------- | --------------------------------------------------------------------------------------------------------------------- |
| Betelgeuse LLC | [Turbo C Programming Using Turbo C++ Compiler](http://www.softwareandfinance.com/Turbo_C/Index.html)                  |
| Shreeharsha P. | [Turbo C Graphics Programming](http://electrosofts.com/cgraphics/)                                                    |
| Trim Tab       | [TASM 5 Intel 8086 Turbo Assembler Download](http://trimtab.ca/2010/tech/tasm-5-intel-8086-turbo-assembler-download/) |
