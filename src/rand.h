#ifndef RAND_H
#define RAND_H

void set_seed(unsigned long new_seed);
float rand_float(const float max);
unsigned char rand_uchar(unsigned int max);
unsigned short rand_ushort(unsigned int max);

#endif