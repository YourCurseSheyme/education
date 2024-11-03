//
// Created by sheyme on 22/09/24.
//
int strdiff(const char *a, const char *b) {
  unsigned char* byte1 = (unsigned char*) a;
  unsigned char* byte2 = (unsigned char*) b;
  int length = 0;
  for (int idx = 0; 1; ++idx) {
    for (int jdx = 0; jdx < 8; ++jdx) {
      if (byte1[idx] == '\0' && byte2[idx] == '\0') {
        return -1;
      }
      unsigned char bit1 = byte1[idx] >> jdx;
      unsigned char bit2 = byte2[idx] >> jdx;
      if (bit1 == '\0' && bit2 != '\0') {
        if (bit2 & 1) {
          return length;
        }
        ++length;
        continue;
      }
      if (bit1 != '\0' && bit2 == '\0') {
        if (bit1 & 1) {
          return length;
        }
        ++length;
        continue;
      }
      if ((bit1 & 1) != (bit2 & 1)) {
        return length;
      }
      ++length;
    }
  }
}