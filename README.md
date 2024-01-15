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
This will generate an output file named `output.bin`, which contains the relevant font info for rendering each glyph.

# File Format
The first four bytes of the file contain an integer denoting the number of glyphs in the output file.

Each glyph has the following format:

`vert_coords` (48 bytes): An array of 4 vectors (Each vector is an array of 3 4-byte floats) denoting the vertex coordinates of the glyph.

`tex_coords` (32 bytes): An array of 4 vectors (Each vector is an array of 2 4-byte floats) denoting the texture coordinates of the glyph for the font's texture image.

`indices` (24 bytes): An array of 2 vectors (Each vector is an array of 3 4-byte integers) denoting the indices of each triange which makes up the glyph quad. Used primarily for generating the element buffer object of the glyph in OpenGL.

`height` (4 bytes): 4-byte float representing the height of the glyph as a ratio of some arbitrary line height

`width` (4 bytes): 4-byte float representing the width of the glyph as a ratio of some arbitrary line height

`advance` (4 bytes): 4-byte float representing how far in the x direction the following glyph should be rendered after the current glyph, as a ratio of some arbitrary line height

`id` (4 bytes): 4-byte integer representing the id of the character in the ascii table

## Rendering Process:
The `vert_coords`, `tex_coords` and `indices` of each glyph can be used to generate a VBO (Vertex buffer object) and EBO (Element buffer object) to render each glpyh.

For simplicity of rendering, the origin of each glpyh is located at the cursor position defined in [this diagram](https://www.angelcode.com/products/bmfont/doc/render_text.html).

To render text, simply place the first glyph in your scene, where its origin is located on the "line" at which the text will be rendered. Then, successive characters are rendered with an x offset given by the `advance` attribute. To scale the text, simply scale the glyph mesh by your arbitrary line height, while also scaling `advance` by line height as well.
