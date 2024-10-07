#ifdef PACTF_ENABLE
#ifndef PACTF_SUITE

// Dependencies
#include <stdio.h>
#include <string.h>

// Constants
#define PACTF_STR_BUF_LEN 50
#define PACTF_PREFIX_BUF_LEN 10
#define P_STRINGIFY(x) #x

// Loggers
#define P_LOG(...) printf(__VA_ARGS__);
#define P_LOG_BOLD(...)                                                        \
  {                                                                            \
    char buf[PACTF_STR_BUF_LEN];                                               \
    sprintf(buf, __VA_ARGS__);                                                 \
    P_LOG("%s%s%s", "\033[1m", buf, "\033[0m");                                \
  }
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
      P_LOG_RED("%s%s evaluates to false\n", pactf_assert_prefix,              \
                P_STRINGIFY(__VA_ARGS__));                                     \
      pactf_errors++;                                                          \
    }                                                                          \
  }

// Helpers
#define P_FUNCTION(name, __VA_ARGS__)                                          \
  {                                                                            \
    char pactf_test_prefix[PACTF_PREFIX_BUF_LEN] = "- ";                       \
    (void)pactf_test_prefix;                                                   \
    char pactf_assert_prefix[PACTF_PREFIX_BUF_LEN] = "    ";                   \
    (void)pactf_assert_prefix;                                                 \
                                                                               \
    P_LOG_BOLD("\n# %s\n", name);                                               \
    { __VA_ARGS__ }                                                            \
  }

#define P_TEST(name, ...)                                                      \
  P_LOG("%s%s\n", pactf_test_prefix, name);                                    \
  if (pactf_before_each) {                                                     \
    pactf_before_each();                                                       \
  }                                                                            \
  { __VA_ARGS__ }                                                              \
  if (pactf_after_each) {                                                      \
    pactf_after_each();                                                        \
  }

#define P_BEFORE_EACH(...)                                                     \
  void pactf_before_each() { __VA_ARGS__ }

#define P_AFTER_EACH(...)                                                      \
  void pactf_after_each() { __VA_ARGS__ }

// Core
#define PACTF_SETUP(...)                                                       \
  void pactf_before_each() __attribute__((weak));                              \
  void pactf_after_each() __attribute__((weak));                               \
  __VA_ARGS__

#define PACTF_SUITE(...)                                                       \
  void pactf_before_each() __attribute__((weak));                              \
  void pactf_after_each() __attribute__((weak));                               \
                                                                               \
  int main() {                                                                 \
    char pactf_empty_fn_name[PACTF_STR_BUF_LEN] = "";                          \
    (void)pactf_empty_fn_name;                                                 \
    char pactf_test_prefix[PACTF_PREFIX_BUF_LEN] = "";                         \
    (void)pactf_test_prefix;                                                   \
    char pactf_assert_prefix[PACTF_PREFIX_BUF_LEN] = "  ";                     \
    (void)pactf_assert_prefix;                                                 \
    int pactf_errors = 0;                                                      \
                                                                               \
    { __VA_ARGS__ }                                                            \
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
