#!/bin/sh



EXEC=""
ARGS="--verbose 7  --addxmlinfo --createxslt --debug  --out_path "


if [ -e ../Releaselinux64 ]
then
    EXEC="../Releaselinux64/ca_qxmlc "
    LIBS="../Releaselinux64/libca_logger_static.a  ../Releaselinux64/libxmlca_static.a"
else
if [ -e ../Releaselinux32 ]
then
    EXEC="../Releaselinux32/ca_qxmlc "
    LIBS="../Releaselinux32/libca_logger_static.a  ../Releaselinux32/libxmlca_static.a"
else
    echo "no exec file"
    echo "please rebuild project in RELEASE mode"
    exit 1
fi
fi





if [ $# -eq 0 ]
then
        echo " create_dylib.sh < xml model file.xml >"
	exit 1 
fi





rm -rf libs
mkdir -p ./libs
cp $LIBS ./libs/.
rm -rf src
rm -rf inc
mkdir -p src inc
echo "DO : $EXEC $ARGS src  $1"
$EXEC $ARGS "src"  $1
mv src/*.h inc/.
rm -rf build
rm -rf dist
mkdir -p build dist
pushd  ./build
cmake -D CMAKE_BUILD_TYPE=RELEASE  -D CMAKE_INSTALL_PREFIX=../dist   ..
cmake --build . --target install
popd
ls -al dist


exit 0
