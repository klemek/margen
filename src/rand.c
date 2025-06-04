#include <math.h>

float seed;

void set_seed(unsigned long new_seed) { seed = (float)(new_seed % 1000000); }

float rand(float seed) {
  float v = powf(seed, 6. / 7.);
  v *= sinf(v) + 1.;
  return v - floorf(v);
}

float rand_float(const float max) { return rand(seed++) * max; }

unsigned char rand_uchar(const unsigned int max) {
  return (unsigned char)(rand(seed++) * max);
}

unsigned short rand_ushort(const unsigned int max) {
  return (unsigned short)(rand(seed++) * max);
}
