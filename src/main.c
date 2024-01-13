#include <main.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "usage: font_loader <input_file>\n");
    return 1;
  }

  FILE *input_file = fopen(argv[1], "rb");
  if (input_file == NULL) {
    fprintf(stderr, "Error: Failed to open input file \"%s\"\n", argv[1]);
    return 1;
  }

  int status = read_font(input_file);

  fclose(input_file);
  return status;
}
