#!/usr/bin/env bash

set -e

executable="./build/FIREDUDE.EXE"
buildlog="./build/TCC.LOG"

if [ ! -f './tools/TC/TCC.EXE' ]
then
    echo 'Error: Turbo C 2.01 compiler needs to be extracted to ./tools/TC/TCC.EXE.'
    exit 3
fi

SDL_VIDEODRIVER=dummy dosbox -conf ./build.dosbox-firedude.conf -noconsole
echo

if [ ! -f "$buildlog" ]
then
    echo 'Error: No build log found.'
    exit 4
elif grep --quiet 'error\|Error\|Undefined symbol' $buildlog
then
    echo 'Error(s) during compilation:'
    echo
    cat $buildlog
    exit 5
elif [ ! -f "$executable" ]
then
    echo 'Error: No executable found.'
    cat $buildlog
    exit 6
fi

cat $buildlog
echo 'Build success!'
