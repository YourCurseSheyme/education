//
// Created by sheyme on 24/09/24.
//
#include <stdio.h>
#include <stdlib.h>

const int kStackSize = 300000;

int wcount(const char* string) {
  if (string == NULL) {
    return 0;
  }
  size_t idx = 0;
  size_t answer = 0;
  char current_char;
  int being_in_word = 0;
  while (string[idx] != '\n') {
    current_char = string[idx];
    ++idx;
    if (current_char == ' ') {
      being_in_word = 0;
      continue;
    }
    if (!being_in_word) {
      being_in_word = 1;
      ++answer;
    }
  }
  return answer;
}

int main() {
  char* string = malloc(kStackSize);
  fgets(string, kStackSize, stdin);
  printf("%d", wcount(string));
  free(string);
}