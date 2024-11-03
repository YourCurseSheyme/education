//
// Created by sheyme on 22/09/24.
//
#include <stdio.h>

const size_t kSize = 8;
const size_t kInf = 10e9-3;

void CalcFac(long long* fac_size) {
  fac_size[0] = 1;
  for (size_t idx = 1; idx < kSize + 1; ++idx) {
    fac_size[idx] = idx * fac_size[idx - 1];
  }
}

void Reverse(long long* array, size_t idx) {
  size_t jdx = kSize - 1;
  while (idx < jdx) {
    long long temp = array[idx];
    array[idx] = array[jdx];
    array[jdx] = temp;
    ++idx;
    --jdx;
  }
}

long long GetNumber(const long long* array, const long long* fac_size) {
  long long answer = 1;
  for (int idx = 0; idx < kSize; ++idx) {
    for (int jdx = idx + 1; jdx < kSize; ++jdx) {
      if (array[idx] > array[jdx]) {
        answer += fac_size[kSize - 1 - idx];
      }
    }
  }
  return answer;
}

void GetNextPermutation(long long* array) {
  size_t idx = kSize - 2;
  while (idx != 0) {
    if (array[idx] < array[idx + 1]) {
      break;
    }
    --idx;
  }
  size_t jdx = idx + 1;
  for (size_t kdx = jdx; kdx < kSize; ++kdx) {
    if (array[kdx] <= array[jdx] && array[idx] < array[kdx]) {
      jdx = kdx;
    }
  }
  long long temp = array[idx];
  array[idx] = array[jdx];
  array[jdx] = temp;
  Reverse(array, idx + 1);
}

char* Permutations(long long* first, long long* second) {
  long long fac_size[kSize + 1];
  CalcFac(fac_size);
  long long first_number = GetNumber(first, fac_size);
  long long second_number = GetNumber(second, fac_size);
  if (first_number < second_number) {
    while (first_number != second_number) {
      GetNextPermutation(first);
      ++first_number;
    }
  } else if (second_number < first_number) {
    while (first_number != second_number) {
      GetNextPermutation(second);
      ++second_number;
    }
  }
  for (size_t idx = 0; idx < kSize; ++idx) {
    if (first[idx] != second[idx]) {
      return "no";
    }
  }
  return "yes";
}

int Comparator(const long long* array, size_t length, long long value) {
  if (length == 1) {
    return 0;
  }
  for (size_t idx = 0; idx < length - 1; ++idx) {
    if (value == array[idx]) {
      return 1;
    }
  }
  return 0;
}

int main() {
  long long first[kSize];
  long long second[kSize];
  long long value = 0;
  for (size_t count = 0; count < kSize * 2; ++count) {
    scanf("%lld", &value);
    size_t flag = 0;
    if (count < kSize) {
      while (Comparator(first, count + 1, value)) {
        ++flag;
        value += -flag * kInf;
      }
      first[count] = value;
    } else {
      while (Comparator(second, count - kSize + 1, value)) {
        ++flag;
        value += -flag * kInf;
      }
      second[count - kSize] = value;
    }
  }
  printf("%s", Permutations(first, second));
}