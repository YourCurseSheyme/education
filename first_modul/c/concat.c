//
// Created by sheyme on 02/10/24.
//
#define  _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t CalcLen(const char* string) {
  size_t len = 0;
  while (string[len] != '\0' && string[len] != '\n') {
    ++len;
  }
  return len;
}

//char* Realloc(char* string, const size_t kSize) {
//  size_t new_size = 2 * kSize;
//  char* answer = malloc(new_size * sizeof(char));
//  memcpy(answer, string, kSize);
//  free(string);
//  return answer;
//}

char* concat(char** strings, const int kNumber) {
  char* answer = malloc(sizeof(char));
  answer[0] = '\0';
  size_t size = sizeof(char);
  size_t length = 0;
  for (size_t idx = 0; idx < kNumber; ++idx) {
    size_t add_len = CalcLen(strings[idx]);
    while (size < add_len + length + 1) {
      size *= 2;
      answer = realloc(answer, size);
    }
    memcpy(answer + length, strings[idx], add_len);
    length += add_len;
    answer[length] = '\0';
  }
  return answer;
}

int main() {
  size_t number = 0;
  scanf("%zu\n", &number);
//  char* strings[number];
  char** strings = malloc(number * sizeof(char*));
  for (size_t idx = 0; idx < number; ++idx) {
    strings[idx] = NULL;
    size_t input_size = 0;
    getline(&strings[idx], &input_size, stdin);
  }
  char* answer = concat(strings, number);
  printf("%s", answer);
  for (size_t idx = 0; idx < number; ++idx) {
    free(strings[idx]);
  }
  free(strings);
  free(answer);
}