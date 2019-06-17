#!/bin/sh

if [ "$1" == "" ]
then
	echo "usage ./verfy.sh <num test> "
	exit 1
fi


file1="./TEST_FILES/test""$1""/file""$1"".cpp"
file2="./TEST_FILES/test""$1""/file""$1"".h"
file3="./TEST_FILES/test""$1""/file""$1"".xml"

cp $file1 "./ca_private/model.cpp"
cp $file2 "./ca_private/model.h"
cp $file3 "./ca_private/model.xml"


sed -i "s/file$1.h/model.h/g" "./ca_private/model.cpp"
