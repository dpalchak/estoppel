#!/bin/bash

ESTP_ROOT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"

for ARCH in host arm
do
    mkdir -p $ESTP_ROOT_DIR/build/$ARCH
    cd $ESTP_ROOT_DIR/build/$ARCH
    echo
    echo
    echo Configuring build/$ARCH for \'$ARCH\' architecture
    echo
    cmake $ESTP_ROOT_DIR -DESTP_ARCH=$ARCH
done
