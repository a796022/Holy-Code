#!/bin/bash

make

if [ $? -eq 0 ]; then
    sudo -E bin/wizard
fi

# make clean

# make valgrind > valgrind_output.txt 2>&1

# make debug