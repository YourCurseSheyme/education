//
// Created by sheyme on 02/10/24.
//
static int Compare(unsigned long idx, unsigned long jdx,
                   int (*less)(unsigned long i, unsigned long j)) {
  int answer = less(jdx, idx) ||
      (!(less(jdx, idx)) && !(less(idx, jdx)));
  return answer;
}

unsigned long peak(unsigned long nel,
                   int (*less)(unsigned long i, unsigned long j)) {
  if (nel == 1) {
    return 0;
  }
  if (Compare(0, 1, less)) {
    return 0;
  }
  for (unsigned long idx = 1; idx < nel - 1; ++idx) {
    if (Compare(idx, idx - 1, less)) {
      if (Compare(idx, idx + 1, less)) {
        return idx;
      }
    }
  }
  if (Compare(nel - 1, nel - 2, less)) {
    return nel - 1;
  }
  return nel;
}