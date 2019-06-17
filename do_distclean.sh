rm -rf Debug*
rm -rf Release*
rm -rf dist
rm -rf CMakeFiles
rm -rf .idea
rm -rf ca_qxmlc/CMakeFiles
rm -rf ca_libxmlca/CMakeFiles
rm -rf ca_test/CMakeFiles
rm -rf ca_logger/CMakeFiles
find . -name cmake_install.cmake -exec rm {} +
find . -name CMakeCache.txt  -exec rm {} +
find . -name Makefile  -exec rm {} +
git status > /dev/null  2&>1
if [ $? -eq 0 ]
then
    ALL=$(git ls-files --others --exclude-standard)
    for ii in $ALL ; do rm -rf $ii; done
fi

