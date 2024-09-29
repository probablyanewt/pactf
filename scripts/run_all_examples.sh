#! /bin/bash

run_example () {
  cd $1
  make run_tests
  cd ..
}

export -f run_example
cd examples
find . -maxdepth 1 -mindepth 1 -type d | xargs -n 1 -I {} bash -c 'run_example "$@"' _ {}

