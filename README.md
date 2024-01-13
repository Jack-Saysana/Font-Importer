# Font-Importer
A simple program which imports BMF font files created utilizing the [Bitmat Font Generator Tool](https://www.angelcode.com/products/bmfont/), and outputs organized character information files for usage in [my graphics engine](https://github.com/Jack-Saysana/OpenGL-Graphics-Engine).

# Compiling (Windows and Linux)
Simply run the makefile in the project root to generate a `/bin` directory with the program binaries inside.

# Usage
For the font of your choice, generate a BMF .fnt binary file utilizing the [Bitmat Font Generator Tool](https://www.angelcode.com/products/bmfont/). (As far as I'm aware, the tool only works on Windows, but you can still compile and run the font importer on Linux utilizing binaries generated on Windows)

Then, run the font importer on the font binary:
```
./bin/Font_Importer <path/to/font/file>
```

## TODO
Right now, the tool will output the font info to the console, which is not currently useful. The tool will be updated to output font info in a standardized and easy to parse output for text rendering.
