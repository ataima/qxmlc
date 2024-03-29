# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)



project (ca_test_build)

include_directories(./inc)
include_directories(../ca_libxmlca/inc) 
include_directories(../ca_logger/inc )


 
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "./src/*.cpp")

ADD_EXECUTABLE(ca_test_build ${SOURCES})

install ( TARGETS ca_test_build DESTINATION ${CMAKE_INSTALL_PREFIX} )

set(CMAKE_CXX_FLAGS "--std=c++14 ${CMAKE_CXX_FLAGS}")


target_link_libraries (ca_test_build xmlca_static )
target_link_libraries (ca_test_build ca_logger_static )
target_link_libraries (ca_test_build pthread )


add_custom_command (
    TARGET ca_test_build
    PRE_BUILD
    COMMAND  ${CMAKE_CURRENT_SOURCE_DIR}/beauty.sh ${CMAKE_CURRENT_SOURCE_DIR}
)


add_custom_target( ca_test
    DEPENDS  ca_test_build
    COMMAND  ${CMAKE_INSTALL_PREFIX}/ca_test_build -f15 out
    WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}
    COMMENT "run all tests  "
)

