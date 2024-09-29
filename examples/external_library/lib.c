#include "../../pactf.h"
#include "./include/external.h"

int do_a_thing(int first, int second) { return first + second; }

int do_a_thing_with_external_functions(int arg) {
  some_external_function();
  int value = some_other_external_function(arg);
  if (value == 0) {
    return 0;
  }
  return 1;
}

PACTF_SETUP(

    // This is a function stub. The minimal required definition to appease the
    // compiler.
    void some_external_function() {}

    // This is a function mock which we can control the return value during
    // tests. I would normally suggest trying to avoid doing this as much as
    // possible, but can sometimes be necessary.
    int mock_return_value = 3;
    int some_other_external_function(int arg) { return mock_return_value; }

    P_BEFORE_EACH({ mock_return_value = 3; });

);

PACTF_SUITE({
  P_FUNCTION("do_a_thing", {
    P_TEST("it should return 5 when passed 2 and 3",
           P_ASSERT(do_a_thing(2, 3) == 5));
  });

  P_FUNCTION("do_a_thing_with_external_functions", {
    P_TEST("it should return 0 when some_other_external_function returns 0", {
      mock_return_value = 0;
      P_ASSERT(do_a_thing_with_external_functions(7) == 0);
    });

    P_TEST("it should return 1 when some_other_external_function returns anything non 0", {
      mock_return_value = 69;
      P_ASSERT(do_a_thing_with_external_functions(7) == 1);
    });
  });
});
