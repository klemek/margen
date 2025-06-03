#include <stdlib.h>

#define HEADER_SIZE 54

char *bmp_header(unsigned long width, unsigned long height, unsigned long color_depth);
unsigned long bmp_data_line_length(unsigned long width, unsigned long color_depth);
char *bmp_data_line(unsigned long width, unsigned long color_depth, char *data, unsigned long data_offset);
unsigned long bmp_data_length(unsigned long width, unsigned long height, unsigned long color_depth);
char *bmp_data(unsigned long width, unsigned long height, unsigned long color_depth, char *data);