#!/bin/bash

BUILD=../build-text2xml-Imported_Kit_ce422a-Debug
GAMA=../gama/bin/gama-local

GKF=`find ${BUILD}/tests -name *.gkf`

for f in ${GKF}
do
    echo $f
    ${GAMA} $f --text /tmp/test.txt
done
