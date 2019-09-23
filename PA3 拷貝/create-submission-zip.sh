#!/usr/bin/env bash

zip -r ./submission.zip ./src/*.h* ./src/*.c* Makefile -x "*.DS_Store" -x "__MACOSX"
