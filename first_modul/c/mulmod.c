//
// Created by sheyme on 22/09/24.
//
#include <stdio.h>

long long k_modula = 0;

void CalcCoefs(unsigned long long* value, int* coefs) {
  unsigned char* bytes = (unsigned char*) value;
  unsigned char bit;
  for (size_t idx = 0; idx < sizeof(value); ++idx) {
    for (size_t jdx = 0; jdx < 8; ++jdx) {
      bit = (bytes[idx] >> jdx) & 1;
      if (bit & 1) {
        coefs[(idx * sizeof(long long)) + jdx] = 1;
      } else {
        coefs[(idx * sizeof(long long)) + jdx] = 0;
      }
    }
  }
}

long long MulMod(unsigned long long value, const int* coefs) {
  unsigned long long residue = value % k_modula;
  unsigned long long answer = residue * coefs[sizeof(long long) * 8 - 1];
  for (size_t idx = 1; idx < sizeof(long long) * 8; ++idx) {
    answer = ((2 * answer) % k_modula + residue * coefs[sizeof(long long) * 8 - 1 - idx]) % k_modula;
  }
  return answer;
}

int main() {
  unsigned long long first = 0;
  unsigned long long second = 0;
  int coefs[sizeof(long long) * 8];
  scanf("%lld %lld %lld", &first, &second, &k_modula);
  CalcCoefs(&second, coefs);
  printf("%lld", MulMod(first, coefs));
}