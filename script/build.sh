#!/bin/bash

mkdir -p data
mkdir -p data/img

cmake -B build
cmake --build build
