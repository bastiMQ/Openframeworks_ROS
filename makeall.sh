#!/bin/bash

makeall(){
    echo $1
    cd $1
    make $2

    for FILE in `ls $1`
        do
           local FULL=$1/${FILE}
           if [ -d $FULL ]; then makeall $FULL $2
           fi
        done
}

makeall `pwd` $1

