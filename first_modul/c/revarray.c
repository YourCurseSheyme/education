//
// Created by sheyme on 22/09/24.
//
#include <stdio.h>
void revarray(void* base, size_t nel, size_t width) {
  unsigned char* bytes = (unsigned char*) base;
  size_t idx = 0;
  size_t jdx = (nel - 1) * width;
  unsigned char temp_value;
  while (idx < jdx) {
    for (size_t kdx = 0; kdx < width; ++kdx) {
      temp_value = *(bytes + jdx + kdx) ^ 0;
      *(bytes + jdx + kdx) = *(bytes + idx + kdx) ^ 0;
      *(bytes + idx + kdx) = temp_value;
    }
    idx += width;
    jdx -= width;
  }
}