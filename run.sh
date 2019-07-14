#!/usr/bin/env bash

set -e

executable="./build/FIREDUDE.EXE"

if [ -f "$executable" ]
then
    dosbox -conf ./run.dosbox-firedude.conf
else
    echo "Error: $executable is missing."
    exit 3
fi
