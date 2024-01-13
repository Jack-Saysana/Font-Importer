#include <font_output.h>

int output_characters() {
  FILE *output_file = fopen("output.bin", "wb");
  if (output_file == NULL) {
    fprintf(stderr, "Error: Unable to create output file\n");
    return 1;
  }

  fwrite(&num_chars, sizeof(int32_t), 1, output_file);
  for (int32_t i = 0; i < num_chars; i++) {
    // Character x offset as a ratio of line height
    float x_offset_ratio = chars[i].x_offset / common.line_height;
    // Character width as a ratio of line height
    float width_ratio = chars[i].width / common.line_height;
    // Character height as a ratio of line height
    float height_ratio = chars[i].height / common.line_height;
    // Advance length as a ratio of line height
    float advance_ratio = chars[i].x_advance / common.line_height;

    // Left most x value of character texture as a ratio of texture width
    float x_tex = chars[i].x / common.scale_w;
    // Top most y value of the character texture as a ratio of texture height
    float y_tex = chars[i].y / common.scale_h;
    // Width of character as a ratio of texture width
    float width_tex = chars[i].width / common.scale_w;
    // Height of character as a ratio of texture height
    float height_tex = chars[i].height / common.scale_h;

    CHARACTER new_char = {
      // Vertex coordinates
      { { -x_offset_ratio, height_ratio, 0.0 },
        { -x_offset_ratio, 0.0, 0.0 },
        { width_ratio - x_offset_ratio, 0.0, 0.0 },
        { width_ratio - x_offset_ratio, height_ratio, 0.0 } },
      // Texture coordinates
      { { x_tex, y_tex },
        { x_tex, y_tex - height_tex },
        { x_tex + width_tex, y_tex - height_tex },
        { x_tex + width_tex, y_tex } },
      // Indicies
      { { 0, 1, 3 },
        { 2, 3, 1 } },
      height_ratio, // Height
      width_ratio, // Width
      advance_ratio // Advance
    };
    fwrite(&new_char, sizeof(CHARACTER), 1, output_file);
  }
  fprintf(stdout, "Successfully created output font to \"output.bin\"\n");
  fclose(output_file);

  return 0;
}
