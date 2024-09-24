//
// Created by sheyme on 20/09/24.
//
#include <stdio.h>

const long long kMinValue = (long long int) -9223372036854775808;

int main() {
  size_t number = 0;
  size_t length = 0;
  long long value = 0;
  long long answer = kMinValue;
  long long temp_sum = 0;

  scanf("%zd", &number);
  long long data[number + 1];
  data[0] = 0;
  for (int count = 1; count <= number; ++count) {
    scanf("%lld", &value);
    data[count] = value + data[count - 1];
  }
  scanf("%zd", &length);

  for (size_t jdx = length; jdx < number + 1; ++jdx) {
    temp_sum = data[jdx] - data[jdx - length];
    if (temp_sum > answer) {
      answer = temp_sum;
    }
  }
  printf("%lld", answer);
}