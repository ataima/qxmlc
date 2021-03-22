# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
# this project create  a dynamic library from source xml to import over other languages
# ex python
# 1 ) create xml model to import
# 2 ) create source from ca_qxml
# 3 ) do cmake and create libca_xml_lib.so
# 4 ) import in python ...
#
cmake_minimum_required (VERSION 2.8.11)



project (ca_xml_dylib)

include_directories(./inc)
 
 
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "./src/*.cpp")


add_library (ca_xml_lib SHARED ${SOURCES} )
add_library (ca_xml_lib_static STATIC ${SOURCES} )


install ( TARGETS ca_xml_lib DESTINATION ${CMAKE_INSTALL_PREFIX} )
install ( TARGETS ca_xml_lib_static DESTINATION ${CMAKE_INSTALL_PREFIX} )

set(CMAKE_CXX_FLAGS "--std=c++14 -fPIC ${CMAKE_CXX_FLAGS}")

add_custom_command (
    TARGET ca_xml_dylib
    PRE_BUILD
    COMMAND  ${CMAKE_CURRENT_SOURCE_DIR}/beauty.sh
)
