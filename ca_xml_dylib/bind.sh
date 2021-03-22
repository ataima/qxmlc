#!/bin/bash

 c++ -O3 -Wall -shared -std=c++14 -fPIC $(python3 -m pybind11 --includes) -I ./inc  ./bind/pybind11.cpp ./src/model.cpp -o ./bind/ca_xml_lib$(python3-config --extension-suffix)
 if [ $? -eq 0 ]
 then
   echo "no error , install on /usr/local/lib/python3.5/dist-packages/ca_xml_lib.cpython-35m-x86_64-linux-gnu.so"
   sudo cp bind/ca_xml_lib.cpython-35m-x86_64-linux-gnu.so /usr/local/lib/python3.5/dist-packages/ca_xml_lib.cpython-35m-x86_64-linux-gnu.so
   [ $? -ne 0 ] && echo 'error on install !!'
 fi
