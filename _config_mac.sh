#!/bin/bash
set -e

CMAKE=cmake

if [[ "$1" == "x" ]]; then
    PROJECT_TYPE="Xcode"
else
    PROJECT_TYPE="Unix Makefiles"
fi

if [[ "$0" = /* ]]; then
    FULL_PATH=$(dirname "$0")
else
    FULL_PATH=$(dirname `find "$PWD/$0"`)
fi

if [ "$PROJECT_TYPE" != "Xcode" ]; then
    BUILD_DIR="buildUnix"
else
    BUILD_DIR="buildXcode"
fi

FULL_BUILD_PATH=$FULL_PATH/$BUILD_DIR

mkdir -p $FULL_BUILD_PATH

cd $FULL_BUILD_PATH

$CMAKE -G "$PROJECT_TYPE" \
    -DFULL_PATH="$FULL_PATH" \
    -DFULL_BUILD_PATH="$FULL_BUILD_PATH" \
    -DPROJECT_TYPE="$PROJECT_TYPE" \
    ..
