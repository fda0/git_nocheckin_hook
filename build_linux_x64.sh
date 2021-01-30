#!/bin/bash
pushd build >> /dev/null

gcc -O2 ../code/source.c -o pre-commit

popd >> /dev/null
