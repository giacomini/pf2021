#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

// integer square root
// for a negative number return 0

int isqrt(int n)
{
  int i = 1;
  while (i * i < n) {
    ++i;
  }
  if (i * i > n) {
    --i;
  }
  return i;
}

TEST_CASE("Testing isqrt") {
  CHECK(isqrt(-2) == 0);
  CHECK(isqrt(-1) == 0);
  CHECK(isqrt(0) == 0);
  CHECK(isqrt(1) == 1);
  CHECK(isqrt(2) == 1);
  CHECK(isqrt(3) == 1);
  CHECK(isqrt(4) == 2);
  CHECK(isqrt(15) == 3);
  CHECK(isqrt(16) == 4);
  CHECK(isqrt(17) == 4);
}
