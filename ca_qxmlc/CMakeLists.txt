# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)



project (ca_qxmlc)

include_directories(./inc)


 
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "./src/*.cpp")

ADD_EXECUTABLE(ca_qxmlc ${SOURCES})

install ( TARGETS ca_qxmlc DESTINATION ${CMAKE_INSTALL_PREFIX} )

set(CMAKE_CXX_FLAGS "--std=c++14 ${CMAKE_CXX_FLAGS}")


target_link_libraries (ca_qxmlc xmlca_static )
target_link_libraries (ca_qxmlc ca_logger_static )
target_link_libraries (ca_qxmlc pthread )


add_custom_command (
    TARGET ca_qxmlc
    PRE_BUILD
    COMMAND  ${CMAKE_CURRENT_SOURCE_DIR}/beauty.sh ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target( test_qxmlc
    DEPENDS  ca_qxmlc
    COMMAND  ${CMAKE_INSTALL_PREFIX}/ca_qxmlc $1 
    WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}
    COMMENT "run qxmlc test "
)

