//
// Created by sheyme on 20/09/24.
//
#include <stdio.h>

void PrintBits(const size_t kSize, void const * const kPtr) {
  unsigned char *bites = (unsigned char*) kPtr;
  unsigned char byte;
  short value = 0;
  for (int idx = 0; idx <= kSize - 1; ++idx) {
    for (int jdx = 0; jdx <= 7; ++jdx) {
      byte = (bites[idx] >> jdx) & 1;
      if (byte == 1) {
        printf("%hd ", value);
      }
      ++value;
    }
  }
}

int main() {
  int set1 = 0;
  int set2 = 0;
  int answer = 0;
  short size = 0;

  scanf("%hd", &size);
  int temp;
  short value = 0;
  for (int count = 0; count < size; ++count) {
    temp = 1;
    scanf("%hd", &value);
    temp <<= value;
    set1 |= temp;
  }

  scanf("%hd", &size);
  for (int count = 0; count < size; ++count) {
    temp = 1;
    scanf("%hd", &value);
    temp <<= value;
    set2 |= temp;
  }

  answer = set1 & set2;
  PrintBits(sizeof(answer), &answer);
}