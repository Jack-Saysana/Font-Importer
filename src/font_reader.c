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

#ifdef DEBUG
  fprintf(stdout, "File id: %s\n", file_id);
  fprintf(stdout, "Format version: %d\n", format_version);
  fprintf(stdout, "=================== READING BLOCKS ===================\n");
#endif

  int8_t block_type = 0;
  int32_t block_size = 0;
  size_t reading_blocks = fread(&block_type, sizeof(char), 1, in_file);
  while (reading_blocks) {
    fread(&block_size, sizeof(int32_t), 1, in_file);

#ifdef DEBUG
    fprintf(stdout, "Block type: %d\n", block_type);
    fprintf(stdout, "Block size: %d\n", block_size);
#endif

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
  fread(&info, sizeof(char), B1_STD_SIZE, in_file);
  int name_len = block_size - B1_STD_SIZE;
  info.font_name = malloc(sizeof(char) * name_len);
  fread(info.font_name, sizeof(char), name_len, in_file);

#ifdef DEBUG
  fprintf(stdout, "  Font size: %d\n", info.font_size);
  fprintf(stdout, "  bit_field: %x\n", info.bit_field);
  fprintf(stdout, "  Char set: %d\n", info.char_set);
  fprintf(stdout, "  stretch H: %d\n", info.stretch_H);
  fprintf(stdout, "  aa: %d\n", info.aa);
  fprintf(stdout, "  Padding up: %d\n", info.padding_up);
  fprintf(stdout, "  Padding right: %d\n", info.padding_right);
  fprintf(stdout, "  Padding down: %d\n", info.padding_down);
  fprintf(stdout, "  Padding left: %d\n", info.padding_left);
  fprintf(stdout, "  Spacing horiz: %d\n", info.spacing_horiz);
  fprintf(stdout, "  Spacing vert: %d\n", info.spacing_vert);
  fprintf(stdout, "  Font name: %s\n", info.font_name);
#endif
}

void read_block_2(FILE *in_file, int block_size) {
  fread(&common, sizeof(char), block_size, in_file);

#ifdef DEBUG
  fprintf(stdout, "  Line height: %d\n", common.line_height);
  fprintf(stdout, "  Base: %d\n", common.base);
  fprintf(stdout, "  Scale w: %d\n", common.scale_w);
  fprintf(stdout, "  Scale h: %d\n", common.scale_h);
  fprintf(stdout, "  Pages: %d\n", common.pages);
  fprintf(stdout, "  Bit field: %x\n", common.bit_field);
  fprintf(stdout, "  Alpha: %x\n", common.alpha_chnl);
  fprintf(stdout, "  Red: %x\n", common.red_chnl);
  fprintf(stdout, "  Green: %x\n", common.green_chnl);
  fprintf(stdout, "  Blue: %x\n", common.blue_chnl);
#endif
}

void read_block_3(FILE *in_file, int block_size) {
  int page_name_len = block_size / common.pages;
  pages.page_names = malloc(sizeof(char *) * common.pages);
  for (int i = 0; i < common.pages; i++) {
    pages.page_names[i] = malloc(sizeof(char) * page_name_len);
    fread(pages.page_names[i], sizeof(char), block_size, in_file);

#ifdef DEBUG
    fprintf(stdout, "  page name: %s\n", pages.page_names[i]);
#endif
  }
}

void read_block_4(FILE *in_file, int block_size) {
  num_chars = block_size / sizeof(BLOCK_4);
  chars = malloc(sizeof(BLOCK_4) * num_chars);
  fread(chars, sizeof(BLOCK_4), num_chars, in_file);

#ifdef DEBUG
  for (int i = 0; i < num_chars; i++) {
    fprintf(stdout, "  id: %d (%c)\n", chars[i].id, chars[i].id);
    fprintf(stdout, "  x: %d\n", chars[i].x);
    fprintf(stdout, "  y: %d\n", chars[i].y);
    fprintf(stdout, "  width: %d\n", chars[i].width);
    fprintf(stdout, "  height: %d\n", chars[i].height);
    fprintf(stdout, "  x offset: %d\n", chars[i].x_offset);
    fprintf(stdout, "  y offset: %d\n", chars[i].y_offset);
    fprintf(stdout, "  x advance: %d\n", chars[i].x_advance);
    fprintf(stdout, "  page: %d\n", chars[i].page);
    fprintf(stdout, "  chnl: %d\n", chars[i].chnl);
    fprintf(stdout, "\n");
  }
#endif
}

void read_block_5(FILE *in_file, int block_size) {
  fread(&kerning_pairs, sizeof(BLOCK_5), 1, in_file);
}
