#include <stdio.h>
#include <stdint.h>
#include <block_str.h>

typedef struct character {
  // Vertex info for rendering
  float vert_coords[4][3];
  float tex_coords[4][2];
  int indices[2][3];

  // Height of character as a ratio of line height
  float height;
  // Width of character as a ratio of line height
  float width;
  /*
  Distance from character center to edge of next character as a ratio of line
  height
  */
  float advance;
} CHARACTER;

extern BLOCK_2 common;
extern BLOCK_4 *chars;
extern int32_t num_chars;
