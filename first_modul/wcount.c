//
// Created by sheyme on 24/09/24.
//
#include <stdio.h>
#include <stdlib.h>

const int kStackSize = 600000;

int wcount(const char* string) {
  size_t idx = 0;
  size_t answer = 0;
  int being_in_word = 0;
  while (string[idx] != '\n') {
    ++idx;
    if (string[idx] == ' ') {
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