# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)



project (ca_xmlca)

include_directories(./inc ../ca_logger/inc )
 
 
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "./src/*.cpp")
file(GLOB HEADERS "./inc/*.h")


add_library (xmlca_static   STATIC ${SOURCES} inc/caqxmlc.h src/caqxmlc.cpp inc/caargopt.h src/caargopt.cpp  )

add_library (xmlca   SHARED ${SOURCES} inc/caqxmlc.h src/caqxmlc.cpp inc/caargopt.h src/caargopt.cpp  )

install ( TARGETS xmlca_static DESTINATION ${CMAKE_INSTALL_PREFIX} )
install ( TARGETS xmlca  DESTINATION ${CMAKE_INSTALL_PREFIX} )

set(CMAKE_CXX_FLAGS "--std=c++14 -fPIC ${CMAKE_CXX_FLAGS}")

add_custom_command (
    TARGET xmlca
    PRE_BUILD
    COMMAND  ${CMAKE_CURRENT_SOURCE_DIR}/beauty.sh
)
