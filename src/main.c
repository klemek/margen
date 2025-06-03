#include "main.h"

int main()
{
    FILE *fptr;
    fptr = fopen("test.bmp", "w");
    char *header = bmp_header(WIDTH, HEIGHT, COLOR_DEPTH);
    fwrite(header, HEADER_SIZE, 1, fptr);
    free(header);
    int y;
    char *data = malloc(WIDTH * COLOR_DEPTH);
    char *data_line = NULL;
    for (y = 0; y < HEIGHT; y++)
    {
        memset(data, HEIGHT - y - 1, WIDTH * COLOR_DEPTH);
        data_line = bmp_data_line(WIDTH, COLOR_DEPTH, data, 0);
        fwrite(data_line, bmp_data_line_length(WIDTH, COLOR_DEPTH), 1, fptr);
        free(data_line);
    }
    free(data);
    return 0;
}