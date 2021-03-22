if [ -e ./Debuglinux* ]
then 
./Debuglinux*/ca_packfile --out capackedfiles ca_private/caminiXml.h ca_libxmlca/inc/calcfxml.h TEST_FILES/test1/Makefile
fi

if [ -e ./Releaselinux* ]
then
./Releaselinux*/ca_packfile --out capackedfiles ca_private/caminiXml.h ca_libxmlca/inc/calcfxml.h TEST_FILES/test1/Makefile
fi
