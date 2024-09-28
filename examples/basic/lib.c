#include "../../pactf.h"

int add_two_numbers(int first, int second) { return first + second; }

int subtract_two_numbers(int first, int second) { return first - second; }

PACTF_SUITE({
  P_FUNCTION("add_two_numbers", {
    P_TEST("it should return 5 when passed 2 and 3",
           P_ASSERT(add_two_numbers(2, 3) == 5));

    P_TEST("it should not return 8 when passed 3 and 4",
           P_ASSERT(add_two_numbers(3, 4) != 8));
  });

  P_FUNCTION("subtract_two_numbers", {
    P_TEST("it should return 5 when passed 7 and 2",
           P_ASSERT(subtract_two_numbers(7, 2) == 5));

    P_TEST("it should not return 8 when passed 9 and 4",
           P_ASSERT(add_two_numbers(9, 4) != 8));
  });
});
