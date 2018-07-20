#!/bin/bash

ESTP_ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"

$ESTP_ROOT_DIR/bootstrap.sh

for ARCH in host arm
do
    cmake --build $ESTP_ROOT_DIR/build/$ARCH
done
