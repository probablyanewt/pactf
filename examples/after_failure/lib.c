#include "../../pactf.h"

int add_two_numbers(int first, int second) { return first + second; }

PACTF_SUITE({
  P_FUNCTION("after_failure", {
    P_TEST("it should show additional context if a test fails", {
      pactf_test_failure = 1;
      P_AFTER_FAILURE({ P_LOG_RED("%sadditional context\n", pactf_assert_prefix); })
    });

    P_TEST("it should not show additional context if a test passes", {
      P_AFTER_FAILURE({ P_LOG_RED("%sadditional context\n", pactf_assert_prefix); })
    });
  });
});
