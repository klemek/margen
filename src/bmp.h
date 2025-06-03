#include "types.h"

#ifndef BMP_H
#define BMP_H

void bmp_generate(unsigned long width, unsigned long height,
                  unsigned int color_depth, char *file_path,
                  line_fn generate_line);

#endif