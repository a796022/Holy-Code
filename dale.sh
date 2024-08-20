#!/bin/bash

make

if [ $? -eq 0 ]; then
    sudo -E bin/wizard
fi

# make clean