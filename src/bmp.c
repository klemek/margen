#include "bmp.h"
#include <stdio.h>
#include <stdlib.h>

#define HEADER_SIZE 54

void write_str(unsigned char *buffer, unsigned short offset,
               unsigned short size, unsigned char *value) {
  int i;
  for (i = 0; i < size; i++) {
    buffer[offset + i] = (unsigned char)value[i];
  }
}

void write_num(unsigned char *buffer, unsigned short offset,
               unsigned short size, unsigned short value) {
  int i;
  for (i = 0; i < size; i++) {
    buffer[offset + i] = (unsigned char)((value >> (8 * i)) & 0xFFu);
  }
}

void write_nul(unsigned char *buffer, unsigned short offset,
               unsigned short size) {
  int i;
  for (i = 0; i < size; i++) {
    buffer[offset + i] = 0;
  }
}

unsigned char *bmp_header(unsigned short width, unsigned short height,
                          unsigned char color_depth) {
  unsigned char *output = (unsigned char *)malloc(HEADER_SIZE);

  write_str(output, 0x00, 0x02, (unsigned char *)"BM"); // 0x00(2) BM
  write_num(output, 0x02, 0x04,
            HEADER_SIZE + width * height * color_depth); // 0x02(4) file size
  write_nul(output, 0x06, 0x04);              // 0x06(4) application reserved
  write_num(output, 0x0A, 0x04, HEADER_SIZE); // 0x0A(4) data offset
  write_num(output, 0x0E, 0x04, 40);          // 0x0E(4) DIB header size
  write_num(output, 0x12, 0x04, width);       // 0x12(4) width
  write_num(output, 0x16, 0x04, height);      // 0x16(4) height
  write_num(output, 0x1A, 0x04, 1);           // 0x1A(2) color panes
  write_num(output, 0x1C, 0x02, color_depth * 8); // 0x1C(2) bits per pixel
  write_nul(output, 0x1E, 0x04); // 0x1E(4) BI_RGB, no compression
  write_num(output, 0x22, 0x04,
            width * height * color_depth); // 0x22(4) size of raw bitmap data
  write_num(output, 0x26, 0x04, 2835); // 0x26(4) horizontal print resolution
  write_num(output, 0x2A, 0x04, 2835); // 0x2A(4) vertical print resolution
  write_nul(output, 0x2E, 0x04);       // 0x2E(4) color in palette
  write_nul(output, 0x32, 0x04);       // 0x32(4) 0 important colors

  return output;
}

unsigned short bmp_data_line_length(unsigned short width,
                                    unsigned char color_depth) {
  unsigned short line_offset = (width * color_depth) % 4;
  unsigned short line_padding = line_offset > 0 ? 4 - line_offset : 0;
  return width * color_depth + line_padding;
}

void bmp_data_line(unsigned char *buffer, unsigned short width,
                   unsigned char color_depth, unsigned char *data) {
  unsigned short line_offset = (width * color_depth) % 4;
  unsigned short line_padding = line_offset > 0 ? 4 - line_offset : 0;
  write_str(buffer, 0, width * color_depth, data);
  if (line_padding > 0) {
    write_nul(buffer, width * color_depth, line_padding);
  }
}

void bmp_generate(unsigned short width, unsigned short height,
                  unsigned char color_depth, char *file_path,
                  line_fn generate_line) {
  FILE *fptr;
  fptr = fopen(file_path, "w");
  unsigned char *header = bmp_header(width, height, color_depth);
  fwrite(header, HEADER_SIZE, 1, fptr);
  free(header);
  unsigned short y;
  unsigned char *data_buffer = malloc(width * color_depth);
  unsigned char *line_buffer = malloc(bmp_data_line_length(width, color_depth));
  for (y = 0; y < height; y++) {
    generate_line(height - y - 1, data_buffer);
    bmp_data_line(line_buffer, width, color_depth, data_buffer);
    fwrite(line_buffer, bmp_data_line_length(width, color_depth), 1, fptr);
  }
  free(line_buffer);
  free(data_buffer);
  fclose(fptr);
}