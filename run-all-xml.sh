#!/bin/bash

BUILD=../`ls .. | grep build-text2xml`
GAMA=../gama/bin/gama-local

GKF=`find ${BUILD}/tests -name *.gkf`

for f in ${GKF}
do
    bname=$(basename $f)           # a base name with the extension
    ename=${bname%.*}              # extension removed
    tname="/tmp/"${ename}".txt"    # temporary results file
    echo $tname
    ${GAMA} $f --text $tname
done
