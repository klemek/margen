#include "bmp.h"
#include <stdio.h>
#include <stdlib.h>

#define HEADER_SIZE 54

void write_str(unsigned char *buffer, unsigned int offset, unsigned int size,
               unsigned char *value) {
  unsigned int i;
  for (i = 0; i < size; i++) {
    buffer[offset + i] = (unsigned char)value[i];
  }
}

void write_num(unsigned char *buffer, unsigned int offset, unsigned int size,
               unsigned int value) {
  unsigned int i;
  for (i = 0; i < size; i++) {
    buffer[offset + i] = (unsigned char)((value >> (8 * i)) & 0xFFu);
  }
}

void write_nul(unsigned char *buffer, unsigned int offset, unsigned int size) {
  unsigned int i;
  for (i = 0; i < size; i++) {
    buffer[offset + i] = 0;
  }
}

unsigned char *bmp_header(unsigned short width, unsigned short height,
                          unsigned char color_depth) {
  unsigned char *output = (unsigned char *)malloc(HEADER_SIZE);
  unsigned int data_length = ((unsigned int)width) * ((unsigned int)height) *
                             ((unsigned int)color_depth);
  // 0x00(2) BM
  write_str(output, 0x00, 0x02, (unsigned char *)"BM");
  // 0x02(4) file size
  write_num(output, 0x02, 0x04, HEADER_SIZE + data_length);
  // 0x06(4) application reserved
  write_nul(output, 0x06, 0x04);
  // 0x0A(4) data offset
  write_num(output, 0x0A, 0x04, HEADER_SIZE);
  // 0x0E(4) DIB header size
  write_num(output, 0x0E, 0x04, 40);
  // 0x12(4) width
  write_num(output, 0x12, 0x04, width);
  // 0x16(4) height
  write_num(output, 0x16, 0x04, height);
  // 0x1A(2) color panes
  write_num(output, 0x1A, 0x04, 1);
  // 0x1C(2) bits per pixel
  write_num(output, 0x1C, 0x02, color_depth * 8);
  // 0x1E(4) BI_RGB, no compression
  write_nul(output, 0x1E, 0x04);
  // 0x22(4) size of raw bitmap data
  write_num(output, 0x22, 0x04, data_length);
  // 0x26(4) horizontal print resolution
  write_num(output, 0x26, 0x04, 2835);
  // 0x2A(4) vertical print resolution
  write_num(output, 0x2A, 0x04, 2835);
  // 0x2E(4) color in palette (0)
  write_nul(output, 0x2E, 0x04);
  // 0x32(4) important colors (0)
  write_nul(output, 0x32, 0x04);

  return output;
}

unsigned int bmp_data_line_length(unsigned short width,
                                  unsigned char color_depth) {
  unsigned int data_length =
      ((unsigned int)width) * ((unsigned int)color_depth);
  unsigned int line_offset = data_length % 4;
  unsigned short line_padding = line_offset > 0 ? 4 - line_offset : 0;
  return data_length + line_padding;
}

void bmp_data_line(unsigned char *buffer, unsigned short width,
                   unsigned char color_depth, unsigned char *data) {
  unsigned int data_length =
      ((unsigned int)width) * ((unsigned int)color_depth);
  unsigned int line_offset = data_length % 4;
  unsigned short line_padding = line_offset > 0 ? 4 - line_offset : 0;
  write_str(buffer, 0, data_length, data);
  if (line_padding > 0) {
    write_nul(buffer, width * color_depth, line_padding);
  }
}

void bmp_generate(unsigned short width, unsigned short height,
                  unsigned char color_depth, bool descending, char *file_path,
                  line_fn generate_line) {
  FILE *fptr;
  fptr = fopen(file_path, "w");
  unsigned char *header = bmp_header(width, height, color_depth);
  fwrite(header, HEADER_SIZE, 1, fptr);
  free(header);
  unsigned int data_length =
      ((unsigned int)width) * ((unsigned int)color_depth);
  unsigned int line_length = bmp_data_line_length(width, color_depth);
  unsigned char *data_buffer = (unsigned char *)malloc(data_length);
  unsigned char *line_buffer = (unsigned char *)malloc(line_length);
  unsigned short y;
  for (y = 0; y < height; y++) {
    generate_line(y, data_buffer, data_length);
    bmp_data_line(line_buffer, width, color_depth, data_buffer);
    if (descending) {
      fseek(fptr, HEADER_SIZE + (height - y - 1) * line_length, SEEK_SET);
    }
    fwrite(line_buffer, line_length, 1, fptr);
  }
  free(line_buffer);
  free(data_buffer);
  fclose(fptr);
}