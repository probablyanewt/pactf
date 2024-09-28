#ifdef PACTF_ENABLE
#ifndef PACTF_SUITE

// Dependencies
#include <stdio.h>
#include <string.h>

// Constants
#define PACTF_STR_BUF_LEN 50
#define PACTF_PREFIX_BUF_LEN 4

// Loggers
#define P_LOG(...) printf(__VA_ARGS__);
#define P_LOG_COLOUR(colour, ...)                                              \
  {                                                                            \
    char buf[PACTF_STR_BUF_LEN];                                               \
    sprintf(buf, __VA_ARGS__);                                                 \
    P_LOG("%s%s%s", colour, buf, "\033[0m");                                   \
  }
#define P_LOG_GREEN(...) P_LOG_COLOUR("\033[32m", __VA_ARGS__)
#define P_LOG_RED(...) P_LOG_COLOUR("\033[31m", __VA_ARGS__)

// Asserters
#define P_ASSERT(...)                                                          \
  {                                                                            \
    if (__VA_ARGS__) {                                                         \
      P_LOG_GREEN("%sPass\n", pactf_assert_prefix)                             \
    } else {                                                                   \
      P_LOG_RED("%sFail\n", pactf_assert_prefix)                               \
      pactf_errors++;                                                          \
    }                                                                          \
  }

// Helpers
#define P_FUNCTION(name, fn_body)                                              \
  {                                                                            \
    char pactf_fn_name[PACTF_STR_BUF_LEN] = name;                              \
    char pactf_test_prefix[PACTF_PREFIX_BUF_LEN] = "- ";                       \
    char pactf_assert_prefix[PACTF_PREFIX_BUF_LEN] = "    ";                   \
    P_LOG("\n%s\n", name);                                                     \
    { fn_body }                                                                \
  }

#define P_TEST(name, test_body)                                                \
  P_LOG("%s%s\n", pactf_test_prefix, name);                                    \
  if (pactf_before_each) {                                                     \
    pactf_before_each();                                                       \
  }                                                                            \
  { test_body }                                                                \
  if (pactf_after_each) {                                                      \
    pactf_after_each();                                                        \
  }

#define P_BEFORE_EACH(before_each_body)                                        \
  void pactf_before_each() { before_each_body }

#define P_AFTER_EACH(after_each_body)                                          \
  void pactf_after_each() { after_each_body }

// Core
#define PACTF_SETUP(setup_body)                                                \
  void pactf_before_each() __attribute__((weak));                              \
  void pactf_after_each() __attribute__((weak));                               \
  setup_body

#define PACTF_SUITE(tests_body)                                                \
  void pactf_before_each() __attribute__((weak));                              \
  void pactf_after_each() __attribute__((weak));                               \
                                                                               \
  int main() {                                                                 \
    char pactf_fn_name[PACTF_STR_BUF_LEN] = "";                                \
    (void)pactf_fn_name;                                                       \
    char pactf_empty_fn_name[PACTF_STR_BUF_LEN] = "";                          \
    (void)pactf_empty_fn_name;                                                 \
    char pactf_test_prefix[PACTF_PREFIX_BUF_LEN] = "";                         \
    (void)pactf_test_prefix;                                                   \
    char pactf_assert_prefix[PACTF_PREFIX_BUF_LEN] = "  ";                     \
    (void)pactf_assert_prefix;                                                 \
    int pactf_errors = 0;                                                      \
                                                                               \
    { tests_body }                                                             \
                                                                               \
    if (pactf_errors > 0) {                                                    \
      return 1;                                                                \
    }                                                                          \
    return 0;                                                                  \
  }

#endif
#else
#ifndef PACTF_SUITE
#define PACTF_SUITE(...)
#define PACTF_SETUP(...)
#endif
#endif
