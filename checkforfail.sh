#!/bin/bash

#recreate lib and ca_qxmlc
make -C ca_libxmlca  clean install
make -C ca_qxmlc clean install

#set at the fail test
./test.sh $1
#copy the generated sources
./verfy.sh $1
#the on debug at ca_private

 
make -C ca_private clean all


