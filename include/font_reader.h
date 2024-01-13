#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define B1_STD_SIZE (14)

// ================================= STRUCTS =================================

typedef struct block_1 {
  int16_t font_size;
  int8_t bit_field;
  uint8_t char_set;
  uint16_t stretch_H;
  uint8_t aa;
  uint8_t padding_up;
  uint8_t padding_right;
  uint8_t padding_down;
  uint8_t padding_left;
  uint8_t spacing_horiz;
  uint8_t spacing_vert;
  uint8_t outline;
  char *font_name;
} BLOCK_1;


typedef struct block_2 {
  uint16_t line_height;
  uint16_t base;
  uint16_t scale_w;
  uint16_t scale_h;
  uint16_t pages;
  int8_t bit_field;
  uint8_t alpha_chnl;
  uint8_t red_chnl;
  uint8_t green_chnl;
  uint8_t blue_chnl;
} BLOCK_2;

typedef struct block_3 {
  char **page_names;
} BLOCK_3;

typedef struct block_4 {
  uint32_t id;
  uint16_t x;
  uint16_t y;
  uint16_t width;
  uint16_t height;
  int16_t x_offset;
  int16_t y_offset;
  int16_t x_advance;
  uint8_t page;
  uint8_t chnl;
} BLOCK_4;

typedef struct block_5 {
  uint32_t first;
  uint32_t second;
  int16_t amount;
} BLOCK_5;

// ================================= GLOBALS =================================

BLOCK_1 b1;
BLOCK_2 b2;
BLOCK_3 b3;
BLOCK_4 *b4;
BLOCK_5 b5;

// ======================= INTERNALLY DEFINED FUNCTIONS ======================

void read_block_1(FILE *, int);
void read_block_2(FILE *, int);
void read_block_3(FILE *, int);
void read_block_4(FILE *, int);
void read_block_5(FILE *, int);
