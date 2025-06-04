#include <math.h>

float seed;

void set_seed(unsigned long new_seed) { seed = (float)(new_seed % 1000000); }

float rand(float seed) {
  float v = powf(fabs(seed), 6. / 7.);
  v *= sinf(v) + 1.;
  return v - floorf(v);
}

unsigned char rand_uchar(unsigned int max) {
  return (unsigned char)(rand(seed++) * max);
}

unsigned short rand_ushort(unsigned int max) {
  return (unsigned short)(rand(seed++) * max);
}
