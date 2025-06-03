#include "bmp.h"

void write_str(char *buffer, int offset, int size, char *value, int value_offset)
{
    int i;
    for (i = 0; i < size; i++)
    {
        buffer[offset + i] = value[i];
    }
}

void write_num(char *buffer, int offset, int size, unsigned long value)
{
    int i;
    for (i = 0; i < size; i++)
    {
        buffer[offset + i] = (char)((value >> (8 * i)) & 0xFFu);
    }
}

void write_nul(char *buffer, int offset, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        buffer[offset + i] = 0;
    }
}

char *bmp_header(unsigned long width, unsigned long height, unsigned long color_depth)
{
    char *output = (char *)malloc(HEADER_SIZE);

    write_str(output, 0x00, 0x02, "BM", 0);                                    // 0x00(2) BM
    write_num(output, 0x02, 0x04, HEADER_SIZE + width * height * color_depth); // 0x02(4) file size
    write_nul(output, 0x06, 0x04);                                             // 0x06(4) application reserved
    write_num(output, 0x0A, 0x04, HEADER_SIZE);                                // 0x0A(4) data offset
    write_num(output, 0x0E, 0x04, 40);                                         // 0x0E(4) DIB header size
    write_num(output, 0x12, 0x04, width);                                      // 0x12(4) width
    write_num(output, 0x16, 0x04, height);                                     // 0x16(4) height
    write_num(output, 0x1A, 0x04, 1);                                          // 0x1A(2) color panes
    write_num(output, 0x1C, 0x02, color_depth * 8);                            // 0x1C(2) bits per pixel
    write_nul(output, 0x1E, 0x04);                                             // 0x1E(4) BI_RGB, no compression
    write_num(output, 0x22, 0x04, width * height * color_depth);               // 0x22(4) size of raw bitmap data
    write_num(output, 0x26, 0x04, 2835);                                       // 0x26(4) horizontal print resolution
    write_num(output, 0x2A, 0x04, 2835);                                       // 0x2A(4) vertical print resolution
    write_nul(output, 0x2E, 0x04);                                             // 0x2E(4) color in palette
    write_nul(output, 0x32, 0x04);                                             // 0x32(4) 0 important colors

    return output;
}

unsigned long bmp_data_line_length(unsigned long width, unsigned long color_depth)
{
    unsigned long line_offset = (width * color_depth) % 4;
    unsigned long line_padding = line_offset > 0 ? 4 - line_offset : 0;
    return width * color_depth + line_padding;
}

char *bmp_data_line(unsigned long width, unsigned long color_depth, char *data, unsigned long data_offset)
{
    unsigned long line_offset = (width * color_depth) % 4;
    unsigned long line_padding = line_offset > 0 ? 4 - line_offset : 0;
    unsigned long line_length = width * color_depth + line_padding;
    char *output = (char *)malloc(line_length);
    write_str(output, 0, width * color_depth, data, data_offset);
    if (line_padding > 0)
    {
        write_nul(output, width * color_depth, line_padding);
    }
    return output;
}

unsigned long bmp_data_length(unsigned long width, unsigned long height, unsigned long color_depth)
{
    return bmp_data_line_length(width, color_depth) * height;
}

char *bmp_data(unsigned long width, unsigned long height, unsigned long color_depth, char *data)
{
    unsigned long line_offset = (width * color_depth) % 4;
    unsigned long line_padding = line_offset > 0 ? 4 - line_offset : 0;
    unsigned long line_length = width * color_depth + line_padding;
    char *output = (char *)malloc(height * line_length);
    int y, offset, offset_data;
    for (y = 0; y < height; y++)
    {
        offset = y * line_length;
        offset_data = (height - y - 1) * color_depth * width;
        write_str(output, offset, width * color_depth, data, offset_data);
        if (line_padding > 0)
        {
            write_nul(output, offset + width * color_depth, line_padding);
        }
    }
    return output;
}