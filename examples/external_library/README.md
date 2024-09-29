# pactf example - external library

This example features a basic c library with 2 functions, one of which uses functions from another library, and a test suite using pactf. During the `PACTF_SETUP` macro we define a stub for one of the external functions. and a mock for the other. As noted in `lib.c` I would normally suggest trying to avoid using mocks, however, there are some instances where they can be useful. Run the tests from this directory using `make run_tests`.
