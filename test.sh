#!/bin/sh

# FIRST BUILD ALL
if [ "$#" -eq 0 ]
then 
	make clean all install
fi


EXEC=""
ARGS="--verbose 7 --addtest --addxmlinfo --createxslt --debug  --out_path "


if [ -e ./Debuglinux64 ]
then
    EXEC="./Debuglinux64/ca_qxmlc "
    LIBS_STATIC="./Debuglinux64/libca_logger_static.a  ./Debuglinux64/libxmlca_static.a"
    LIBS="./Debuglinux64/libca_logger.so  ./Debuglinux64/libxmlca.so"
else
if [ -e ./Debuglinux32 ]
then
    EXEC="./Debuglinux32/ca_qxmlc "
    LIBS_STATIC="./Debuglinux32/libca_logger_static.a  ./Debuglinux32/libxmlca_static.a"
    LIBS="./Debuglinux32/libca_logger.so  ./Debuglinux32/libxmlca.so"
else
if [ -e ./Releaselinux64 ]
then
    EXEC="./Releaselinux64/ca_qxmlc "
    LIBS_STATIC="./Releaselinux64/libca_logger_static.a ./Releaselinux64/libxmlca_static.a"
    LIBS="./Releaselinux64/libca_logger.so ./Releaselinux64/libxmlca.so"
else
if [ -e ./Releaselinux32 ]
then
    EXEC="./Releaselinux32/ca_qxmlc "
    LIBS_STATIC="./Releaselinux32/libca_logger_static.a  ./Releaselinux32/libxmlca_static.a"
    LIBS="./Releaselinux32/libca_logger.so ./Releaselinux32/libxmlca.so"
else
    echo "no exec file"
    exit 1
fi
fi
fi
fi



unset IFS
declare -i NUMFILES=$(ls --format=single-column testfiles/*.xml | wc -l)



if [ $? -ne 0 ]
then
	echo " testfiles/*.xml no files to test "
	exit 1  
fi  

if [ $NUMFILES -eq 0 ]
then
        echo " testfiles/*.xml no files to test "
	exit 1 
fi


#$1 num...
#$2 file
function testone(){
local N=$1
if ! [[ "$N" =~ ^[0-9]+$ ]]
    then
        echo "Sorry insert test num 0..."$NUMFILES
	exit 1
fi
if [ $N -gt $NUMFILES ]
then
echo "Sorry insert test num 0..."$NUMFILES
        exit 1 
fi
mkdir -p  "TEST_FILES/test"$N
echo "DO : $EXEC $ARGS "TEST_FILES/test"$N  $2"
$EXEC $ARGS "TEST_FILES/test"$N  $2
cp $LIBS  "TEST_FILES/test"$N"/."
cp $LIBS_STATIC  "TEST_FILES/test"$N"/."
pushd  "TEST_FILES/test"$N
make all
if [ $? -ne 0 ]
    then
        echo "TEST_FILES/test"$N build fail
        popd 
        exit 1
fi
sync
LD_LIBRARY_PATH=$PWD time ./test_qxmlc $(basename $2) > "out$N.xml"
if [ $? -ne 0 ]
     then
        echo "TEST_FILES/test"$N check fail
        popd
        exit 1
fi
xmlstarlet fo "out$N.xml"
if [ $? -ne 0 ]
     then
	echo "TEST_FILES/test"$N invalid xml output file "out$N.xml"
	popd 
	exit 1
fi

time ./test_qxmlc_static $(basename $2) > "out$N.xml"
if [ $? -ne 0 ]
     then
        echo "TEST_FILES/test_static"$N check fail
        popd
        exit 1
fi
xmlstarlet fo "out$N.xml"
if [ $? -ne 0 ]
     then
        echo "TEST_FILES/test_static"$N invalid xml output file "out$N.xml"
        popd
        exit 1
fi
popd
return 0
}




function testall(){
rm -rf TEST_FILES
local N=1
while [ $N -le $NUMFILES ]
do
    testone $N "testfiles/file$N.xml"
    N=$((N+1))
done
echo "ALL TEST OK!!!!"
}


mkdir -p TEST_FILES

if [ "$1" == "" ]
then 
	testall
else
	for TT in $@
	do
	  rm -rf "TEST_FILES/test"$TT
	  testone $TT "testfiles/file$TT.xml"
	done
fi 
exit 0
