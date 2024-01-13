#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <block_str.h>

#define B1_STD_SIZE (14)
//#define DEBUG

// ================================= GLOBALS =================================

BLOCK_1 info;
BLOCK_2 common;
BLOCK_3 pages;
BLOCK_4 *chars;
int32_t num_chars = 0;
BLOCK_5 kerning_pairs;

// ======================= INTERNALLY DEFINED FUNCTIONS ======================

void read_block_1(FILE *, int);
void read_block_2(FILE *, int);
void read_block_3(FILE *, int);
void read_block_4(FILE *, int);
void read_block_5(FILE *, int);
