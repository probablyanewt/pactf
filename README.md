# pactf

Probably a C testing framework

## Project goals

1. Create a testing framework for C which enables me to write unit tests inside the file under test.
2. No test code can end up in compiled binaries.
3. C language server should work for the test code, in my case ccls, but others should too.
4. Single header file. I wanted the whole framework to be contained and used from a single header file.
5. As little code as possible. I like my projects to do something specific well, instead of being ok at every configurable possibilty. this has the additional benefit of being much easier to audit and understand.
6. No external library dependencies other than the C standard library.

## How it works

The long and sort of it is the `PACTF_SUITE` macro adds a main function to a C library, enabling you to run it as a binary. This does mean that you can't use pactf in a file with a main function already. If you have code in a main function you want to test, then you'll have to pull it out into a library first.

## Install

### Globally

Do one of the following:

- Clone the repo, and run `make install` as root to copy the `pactf.h` header file to `/usr/include`.
- Clone the repo, and run `make link` as root to create a symlink to the `pactf.h` header file in `/usr/include`. This option can make it slightly easier to update by simply pulling down the repo.
- Just dowload the `pactf.h` file and put it wherever you need to for global header files on your system.

### Within a project

You could add this repo as a git submodule to your project, or simply copy `pactf.h` into your project and use that.

## Write

### Setup LSP

It was important to me that my LSP could identify the code inside the pactf macros when writing the tests. In order to achieve this you need to inform your LSP that things are built with the `ENABLE_PACTF` macro defined, even though when you actually build your project, you won't want that macro defined.

<details>
    <summary>ccls</summary>
    You can configure ccls to recognise the code inside the pactf macros by doing one of:  
    <ul>
        <li>Setting <code>-DPACTF_ENABLE</code> when generating your <code>compile_commands.json</code>.</li>
        <li>Add <code>-DPACTF_ENABLE</code> to your <code>.ccls</code> file. See <code>examples/basic</code> for an example.</li>
    </ul>
</details>
<details>
    <summary>clangd - wip</summary>
    WIP
</details>

### First test

1. Add `PACTF_SUITE` to the bottom of your library. This is going to contain all of the test code to be executed.

```
PACTF_SUITE({

});
```

2. Inside the braces of `PACTF_SUITE` add `P_TEST`. This is how you separate and name your test cases.

```
PACTF_SUITE({
    P_TEST("it should do a thing",{

    });
});
```

3. Inside the braces of `P_TEST` add `P_ASSERT`. This is how you make assertions about your codes behaviour. The code inside the braces of `P_ASSERT` should be an expression that evaluates to a boolean.

```
PACTF_SUITE({
    P_TEST("it should do a thing",{
        P_ASSERT(some_function() == 3);
    });
});
```

4. Done, this is the most basic form of a test.

### Formatting tips

I've had the most success with code formatters by passing a block `{...}` to the macros I can, and ending each macro call with a semicolon. See the below macros section to see which macros support a block as an argument and which don't. Sometimes adding blank lines can help too, particularly inside the macros that don't support blocks, YMMV however.

### The macros

All code arguments support optionally wrapping your code in a block, unless otherwise stated.

#### Core

| Macro               | Explanation                                                                                                                                                                                                                                                                                                                                      |
| ------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| `PACTF_SETUP(code)` | `PACTF_SETUP` is an optional macro which enables you to execute setup code at the file root, outside of the main function. This could be function stubs, `P_BEFORE_EACH`, or `P_AFTER_EACH`. You will need to stub any external functions used in this file, inside this macro\*. The `code` argument does not support being wrapped in a block. |
| `PACTF_SUITE(code)` | `PACTF_SUITE` is the wrapper that should contain all test code that isn't inside `PACTF_SETUP`.                                                                                                                                                                                                                                                  |

\* While it would be possible to use these functions as mocks, I would encourage you not do so. Instead, I would encourage only using these stubs to ensure this file can compile on it's own and only writing unit tests for functions which do not call external functions. This will likely require structuring your code in a certain way.

#### Helpers

| Macro                    | Explanation                                                                                                                                                                                  |
| ------------------------ | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `P_FUNCTION(name, code)` | `P_FUNCTION` is an optional wrapper to help organise your tests by function. Use the `name` argument to label the tests contained in the `code` argument.                                    |
| `P_TEST(name, code)`     | `P_TEST` is the wrapper for your tests. Each tests case should be in it's own `P_TEST` macro. Use the `name` argument to describe what behaviour you are testing for in the `code` argument. |
| `P_BEFORE_EACH(code)`    | `P_BEFORE_EACH` defines a function which is executed before the `code` argument of each use of `P_TEST`.                                                                                     |
| `P_AFTER_EACH(code)`     | `P_AFTER_EACH` defines a function which is executed after the `code` argument of each use of `P_TEST`.                                                                                       |

#### Asserters

| Macro                  | Explanation                                                                                                 |
| ---------------------- | ----------------------------------------------------------------------------------------------------------- |
| `P_ASSERT(expression)` | `P_ASSERT` is the macro used to make test assertions. The `expression` argument must evaluate to a boolean. |

#### Loggers

| Macro                           | Explanation                                                                                                                                 |
| ------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------- |
| `P_LOG(...args)`                | `P_LOG` is simply a macro helper for `printf` and takes the same `args`.                                                                    |
| `P_LOG_COLOUR(colour, ...args)` | `P_LOG_COLOUR` is a macro helper for `printf` and takes the same `args`, but wraps the resultant string in the provided ansi `colour` code. |
| `P_LOG_GREEN(colour, ...args)`  | `P_LOG_RED` is macro for `P_LOG_COLOUR` with the colour hardcoded as green, `"\033[32m"`.                                                   |
| `P_LOG_RED(colour, ...args)`    | `P_LOG_RED` is macro for `P_LOG_COLOUR` with the colour hardcoded as red, `"\033[31m"`.                                                     |

## Run

In order to run the tests, simply compile each file individually with the flag `-DPACTF_ENABLE`, then execute the resultant binary. For example:

```
gcc -DPACTF_ENABLE -o test lib.c
./test
```

You may also need to add include flags to gcc if you're using header files from non standard places.

## Possible future improvements

- I may extend this to be able to run integration tests against complete compiled binaries, however, that may end up being a separate project.
