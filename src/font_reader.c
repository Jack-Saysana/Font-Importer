#include <font_reader.h>

int read_font(FILE *in_file) {
  char file_id[4] = { '\0', '\0', '\0', '\0' };
  char format_version = 0;
  fread(file_id, sizeof(char), 3, in_file);
  fread(&format_version, sizeof(char), 1, in_file);

  if (file_id[0] != 'B' && file_id[1] != 'M' && file_id[2] != 'F') {
    fprintf(stderr, "Error: Invalid input file format\n");
    return -1;
  }

  fprintf(stdout, "File id: %s\n", file_id);
  fprintf(stdout, "Format version: %d\n", format_version);
  fprintf(stdout, "=================== READING BLOCKS ===================\n");

  int block_type = 0;
  int block_size = 0;
  size_t reading_blocks = fread(&block_type, sizeof(char), 1, in_file);
  while (reading_blocks) {
    fread(&block_size, sizeof(int), 1, in_file);

    fprintf(stdout, "Block type: %d\n", block_type);
    fprintf(stdout, "Block size: %d\n", block_size);

    if (block_type == 1) {
      read_block_1(in_file, block_size);
    } else if (block_type == 2) {
      read_block_2(in_file, block_size);
    } else if (block_type == 3) {
      read_block_3(in_file, block_size);
    } else if (block_type == 4) {
      read_block_4(in_file, block_size);
    } else if (block_type == 5) {
      read_block_5(in_file, block_size);
    }

    reading_blocks = fread(&block_type, sizeof(char), 1, in_file);
  }

  return 0;
}

void read_block_1(FILE *in_file, int block_size) {
  fread(&b1, sizeof(char), B1_STD_SIZE, in_file);
  int name_len = block_size - B1_STD_SIZE;
  b1.font_name = malloc(sizeof(char) * name_len);
  fread(b1.font_name, sizeof(char), name_len, in_file);

  fprintf(stdout, "  Font size: %d\n", b1.font_size);
  fprintf(stdout, "  bit_field: %x\n", b1.bit_field);
  fprintf(stdout, "  Char set: %d\n", b1.char_set);
  fprintf(stdout, "  stretch H: %d\n", b1.stretch_H);
  fprintf(stdout, "  aa: %d\n", b1.aa);
  fprintf(stdout, "  Padding up: %d\n", b1.padding_up);
  fprintf(stdout, "  Padding right: %d\n", b1.padding_right);
  fprintf(stdout, "  Padding down: %d\n", b1.padding_down);
  fprintf(stdout, "  Padding left: %d\n", b1.padding_left);
  fprintf(stdout, "  Spacing horiz: %d\n", b1.spacing_horiz);
  fprintf(stdout, "  Spacing vert: %d\n", b1.spacing_vert);
  fprintf(stdout, "  Font name: %s\n", b1.font_name);
}

void read_block_2(FILE *in_file, int block_size) {
  fread(&b2, sizeof(char), block_size, in_file);

  fprintf(stdout, "  Line height: %d\n", b2.line_height);
  fprintf(stdout, "  Base: %d\n", b2.base);
  fprintf(stdout, "  Scale w: %d\n", b2.scale_w);
  fprintf(stdout, "  Scale h: %d\n", b2.scale_h);
  fprintf(stdout, "  Pages: %d\n", b2.pages);
  fprintf(stdout, "  Bit field: %x\n", b2.bit_field);
  fprintf(stdout, "  Alpha: %x\n", b2.alpha_chnl);
  fprintf(stdout, "  Red: %x\n", b2.red_chnl);
  fprintf(stdout, "  Green: %x\n", b2.green_chnl);
  fprintf(stdout, "  Blue: %x\n", b2.blue_chnl);
}

void read_block_3(FILE *in_file, int block_size) {
  int page_name_len = block_size / b2.pages;
  b3.page_names = malloc(sizeof(char *) * b2.pages);
  for (int i = 0; i < b2.pages; i++) {
    b3.page_names[i] = malloc(sizeof(char) * page_name_len);
    fread(b3.page_names[i], sizeof(char), block_size, in_file);

    fprintf(stdout, "  page name: %s\n", b3.page_names[i]);
  }
}

void read_block_4(FILE *in_file, int block_size) {
  int num_chars = block_size / sizeof(BLOCK_4);
  b4 = malloc(sizeof(BLOCK_4) * num_chars);
  fread(b4, sizeof(BLOCK_4), num_chars, in_file);

  for (int i = 0; i < num_chars; i++) {
    fprintf(stdout, "  id: %d (%c)\n", b4[i].id, b4[i].id);
    fprintf(stdout, "  x: %d\n", b4[i].x);
    fprintf(stdout, "  y: %d\n", b4[i].y);
    fprintf(stdout, "  width: %d\n", b4[i].width);
    fprintf(stdout, "  height: %d\n", b4[i].height);
    fprintf(stdout, "  x offset: %d\n", b4[i].x_offset);
    fprintf(stdout, "  y offset: %d\n", b4[i].y_offset);
    fprintf(stdout, "  x advance: %d\n", b4[i].x_advance);
    fprintf(stdout, "  page: %d\n", b4[i].page);
    fprintf(stdout, "  chnl: %d\n", b4[i].chnl);
    fprintf(stdout, "\n");
  }
}

void read_block_5(FILE *in_file, int block_size) {
  fread(&b5, sizeof(BLOCK_5), 1, in_file);
}
