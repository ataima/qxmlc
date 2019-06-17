#!/bin/bash

INPUT=./ca_libxmlca/inc/caminiXml.h
OUTPUT=./ca_private/caminiXml.h
INPUT1=./ca_libxmlca/inc/calcfxml.h
OUTPUT1=./ca_private/calcfxml.h

POS=$(grep --line-number 'class miniXmlNode' $INPUT | sed 's/:/ /p' | sed -n 1p |awk '{print $1}')
POS=$((POS-3))
if [ $POS -gt 0 ]
then
	cat $INPUT | head -n $POS > $OUTPUT
	echo "} // ena CA namespace" >> $OUTPUT
	echo "" >> $OUTPUT
	echo "" >> $OUTPUT
	echo "#endif" >> $OUTPUT
	cp $INPUT1 $OUTPUT1
else
	echo "Error cannot find declration on class miniXmlNode"
	exit 1
fi

exit 0

 
