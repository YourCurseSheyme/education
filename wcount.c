//
// Created by sheyme on 24/09/24.
//
#include <stdio.h>

const int kStackSize = 8 * 1024 * 16 / sizeof(char);

// Variables can be given more meaningful names =)
// s -> string
int wcount(const char* string) {
  size_t idx = 0;
  size_t answer = 0;
  int being_in_word = 0;
  while (string[idx] != '\n') {
    char current_char = string[idx];
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
  char* string[kStackSize];
  fgets(string, kStackSize, stdin);
  printf("%d", wcount(string));
}