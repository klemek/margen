#include "types.h"

#ifndef BMP_H
#define BMP_H

void bmp_generate(unsigned int width, unsigned int height,
                  unsigned int color_depth, bool descending, char *file_path,
                  line_fn generate_line);

#endif