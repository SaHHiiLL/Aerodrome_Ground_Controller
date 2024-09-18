#!/bin/env bash
set -xa

mkdir -p cmake-build-debug

cd cmake-build-debug || exit
cmake .. || exit
cmake --build . || exit

