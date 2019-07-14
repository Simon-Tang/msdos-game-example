#!/usr/bin/env bash

set -e

executable="./build/FIREDUDE.EXE"

if [ -f "$executable" ]
then
    dosbox -conf ./run.dosbox-firedude.conf
else
    echo 'Error: ./build.FIREDUDE.EXE is missing.'
    exit 1
fi
