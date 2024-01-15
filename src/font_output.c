#include <font_output.h>

int output_characters() {
  FILE *output_file = fopen("output.bin", "wb");
  if (output_file == NULL) {
    fprintf(stderr, "Error: Unable to create output file\n");
    return 1;
  }

  float base_ratio = ((float) common.base / (float) common.line_height);

  fwrite(&num_chars, sizeof(int32_t), 1, output_file);
  fwrite(&base_ratio, sizeof(float), 1, output_file);
  for (int32_t i = 0; i < num_chars; i++) {
    // Character x offset as a ratio of line height
    float x_offset_ratio = ((float) chars[i].x_offset) /
                           ((float) common.line_height);
    // Character width as a ratio of line height
    float width_ratio = ((float) chars[i].width) /
                        ((float) common.line_height);
    // Character height as a ratio of line height
    float height_ratio = ((float) chars[i].height) /
                         ((float) common.line_height);
    // Advance length as a ratio of line height
    float advance_ratio = ((float) chars[i].x_advance) /
                          ((float) common.line_height);
    // y_offset as a ratio of line height
    float y_offset_ratio = ((float) chars[i].y_offset) /
                           ((float) common.line_height);

    // Left most x value of character texture as a ratio of texture width
    float x_tex = ((float) chars[i].x) / ((float) common.scale_w);
    // Top most y value of the character texture as a ratio of texture height
    float y_tex = ((float) chars[i].y) / ((float) common.scale_h);
    // Width of character as a ratio of texture width
    float width_tex = ((float) chars[i].width) / ((float) common.scale_w);
    // Height of character as a ratio of texture height
    float height_tex = ((float) chars[i].height) / ((float) common.scale_h);

    CHARACTER new_char = {
      // Vertex coordinates
      { { -x_offset_ratio, height_ratio, 0.0 },
        { -x_offset_ratio, 0.0, 0.0 },
        { width_ratio - x_offset_ratio, 0.0, 0.0 },
        { width_ratio - x_offset_ratio, height_ratio, 0.0 } },
      // Texture coordinates
      { { x_tex, 1.0 - y_tex },
        { x_tex, 1.0 - y_tex - height_tex },
        { x_tex + width_tex, 1.0 - y_tex - height_tex },
        { x_tex + width_tex, 1.0 - y_tex } },
      // Indicies
      { { 0, 1, 3 },
        { 2, 3, 1 } },
      height_ratio, // Height
      width_ratio, // Width
      advance_ratio, // Advance
      x_offset_ratio, // X offset
      y_offset_ratio, // Y offset
      chars[i].id
    };
    fwrite(&new_char, sizeof(CHARACTER), 1, output_file);
  }
  fprintf(stdout, "Successfully created output font to \"output.bin\"\n");
  fclose(output_file);

  return 0;
}
