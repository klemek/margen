typedef void line_fn(unsigned long y, char *data_buffer);

void bmp_generate(unsigned long width, unsigned long height,
                  unsigned int color_depth, char *file_path, line_fn);