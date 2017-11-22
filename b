#!/bin/sh

pushd build
cmake .. && make
popd

