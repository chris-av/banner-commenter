#!/usr/bin/env bash
# VERSION=$(git describe --tags --abbrev=0)
VERSION="0.1.0"
echo "#define PROGRAM_VERSION \"$VERSION\"" > version.h
