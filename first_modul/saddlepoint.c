//
// Created by sheyme on 23/09/24.
//
#include <stdio.h>

size_t column_size = 0;
size_t row_size = 0;
const long long kMax = 9e18;

void CalcMinNMax(const long long* matrix, long long* min_n_max) {
  long long min_value = kMax;
  long long max_value = -kMax;
  for (size_t column = 0; column < row_size; ++column) {
    min_value = kMax;
    for (size_t idx = 0; idx < column_size; ++idx) {
      if (matrix[column + row_size * idx] < min_value) {
        min_value = matrix[column + row_size * idx];
      }
    }
    min_n_max[column] = min_value;
  }
  for (size_t row = 0; row < column_size; ++row) {
    max_value = -kMax;
    for (size_t idx = 0; idx < row_size; ++idx) {
      if (matrix[row_size * row + idx] > max_value) {
        max_value = matrix[row_size * row + idx];
      }
    }
    min_n_max[row_size + row] = max_value;
  }
}

void FindSaddle(const long long* matrix, size_t* answer) {
  long long min_n_max[column_size + row_size];
  CalcMinNMax(matrix, min_n_max);
  for (size_t idx = 0; idx < row_size; ++idx) {
    for (size_t jdx = 0; jdx < column_size; ++jdx) {
      if (min_n_max[idx] == min_n_max[row_size + jdx]) {
        answer[0] = jdx;
        answer[1] = idx;
        return;
      }
    }
  }
}

int main() {
  scanf("%zd %zd", &column_size, &row_size);
  long long matrix[column_size * row_size];
  long long value = 0;
  for (size_t idx = 0; idx < row_size * column_size; ++idx) {
    scanf("%lld", &value);
    matrix[idx] = value;
  }
  size_t answer[2] = {kMax, kMax};
  FindSaddle(matrix, answer);
  if (answer[0] == kMax) {
    printf("none");
  } else {
    printf("%zd %zd", answer[0], answer[1]);
  }
}