
if [ "$1" == "" ]
then 
	echo "usage ./bootstrap.sh 32 or 64"
	exit 1
fi


cmake -DCMAKE_INSTALL_PREFIX=$(pwd)/../Releaselinux$1  -DCMAKE_BUILD_TYPE=Release  -DCMAKE_TOOLCHAIN_FILE=./$1_linux_i686.toolchain.cmake   .
make -j8 all install

rm -rf install_manifest.txt
