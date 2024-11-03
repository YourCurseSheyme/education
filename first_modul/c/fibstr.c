//
// Created by sheyme on 12/10/24.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* fibstr(const size_t kNumber) {
  char* first = malloc(2);
  first[0] = 'a';
  first[1] = '\0';
  size_t first_len = 1;
  if (kNumber == 1) {
    return first;
  }
  char* second = malloc(2);
  second[0] = 'b';
  second[1] = '\0';
  size_t second_len = 1;
  if (kNumber == 2) {
    free(first);
    return second;
  }
  char* answer = malloc(sizeof(char));
  size_t size = 1;
  answer[0] = '\0';
  for (size_t count = 2; count < kNumber; ++count) {
    size_t new_len = first_len + second_len;
    while (size < new_len + 1) {
      size *= 2;
      answer = realloc(answer, size);
    }
    memcpy(answer, first, first_len);
    memcpy(answer + first_len, second, second_len);
    answer[new_len] = '\0';
    free(first);
    first = second;
    first_len = second_len;
    char* copy = malloc(new_len + 1);
    second = copy;
    memcpy(second, answer, new_len + 1);
    second_len = new_len;
  }
  free(first);
  free(second);
  return answer;
}

int main() {
  size_t number = 0;
  scanf("%zu", &number);
  char* answer = fibstr(number);
  printf("%s", answer);
  free(answer);
}