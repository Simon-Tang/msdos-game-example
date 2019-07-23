#!/usr/bin/env bash

rm -rf dist/*
cp -rf build/*.EXE dist/
zip -r dist/FIREDUDE.ZIP dist/* -x '*.zip'
