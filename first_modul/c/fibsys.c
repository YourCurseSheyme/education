//
// Created by sheyme on 20/09/24.
//
#include <stdio.h>

void PrintBits(size_t const kSize, void const * const kPtr, const int kFlag) {
  unsigned char *bites = (unsigned char*) kPtr;
  unsigned char byte;
  static int flag = 0;
  for (int idx = kSize - 1; idx >= 0; --idx) {
    for (int jdx = 7; jdx >= 0; --jdx) {
      byte = (bites[idx] >> jdx) & 1;
      if (byte == 1) {
        flag = 1;
      }
      if (flag == 0) {
        continue;
      }
      if (jdx == 0 && idx == 0 && kFlag == 0) {
        return;
      }
      printf("%u", byte);
    }
  }
}

int main() {
  unsigned long long number = 0;
  unsigned long long answer = 0;
  unsigned long long additional_head = 0;
  scanf("%lld", &number);
  if (number == 0) {
    printf("%u", 0);
  }

  while (number != 0) {
    int counter = 0;
    unsigned long long first = 1;
    unsigned long long second = 1;
    unsigned long long temp_value = 1;
    unsigned long long additional_temp_value = 1;

    while (first + second <= number) {
      ++counter;
      second += first;
      first = second - first;
      temp_value <<= 1;
      if (counter > 63) {
        additional_temp_value <<= 1;
      }
    }
    number -= second;
    if (counter > 63) {
      additional_head |= additional_temp_value;
    }
    answer |= temp_value;
  }

  PrintBits(sizeof(additional_head), &additional_head, 0);
  PrintBits(sizeof(answer), &answer, 1);
}