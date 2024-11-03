//
// Created by sheyme on 02/10/24.
//
#include <stdio.h>

long long Sqrt(const long long kNumber) {
  long long left = 1;
  long long right = kNumber;
  while (right > left) {
    long long middle = (left + right) / 2;
    if (middle * middle == kNumber) {
      return middle;
    }
    if (middle * middle < kNumber) {
      left = middle + 1;
    } else {
      right = middle - 1;
    }
  }
  return left;
}

long long Sieve(long long number) {
  long long divider = 1;
  if (number <= 1 && number >= -1) {
    return divider - (number == 0);
  }
  long long stop_point = 1;
  if (number < 0) {
    stop_point = -1;
  }
  number = number < 0 ? -number : number;
  long long checker = Sqrt(number);
  while (number != stop_point) {
    if (divider <= 2) {
      ++divider;
    } else {
      divider += 2;
      if (divider > checker) {
        return number;
      }
    }
    while (number % divider == 0) {
      number /= divider;
    }
  }
  return divider;
}

int main() {
  long long number;
  scanf("%lld", &number);
  printf("%lld", Sieve(number));
}