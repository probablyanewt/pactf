#include "../../pactf.h"

typedef struct {
  int value;
} State;

static State state = {.value = 5};

void state_add_value(int value) { state.value += value; }

void state_subtract_value(int value) { state.value -= value; }

PACTF_SETUP(

    P_BEFORE_EACH({ state.value = 5; });

);

PACTF_SUITE({
  P_FUNCTION("state_add_value", {
    P_TEST("it should add value to state.value", {
      state_add_value(2);
      P_ASSERT(state.value == 7)
    });
  });

  P_FUNCTION("state_subtract_value", {
    P_TEST("it should subtract value from state.value", {
      state_subtract_value(2);
      P_ASSERT(state.value == 3);
    });
  });
});
