# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)



project (ca_private)

include_directories(./inc)


 
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "./*.cpp")


ADD_EXECUTABLE(ca_private ${SOURCES})

install ( TARGETS ca_private  DESTINATION ${CMAKE_INSTALL_PREFIX} )

set(CMAKE_CXX_FLAGS "--std=c++14 ${CMAKE_CXX_FLAGS}")

target_link_libraries (ca_private xmlca_static )
target_link_libraries (ca_private ca_logger_static )
target_link_libraries (ca_private pthread )


add_custom_command (
    TARGET ca_private
    PRE_BUILD
    COMMAND  ${CMAKE_CURRENT_SOURCE_DIR}/beauty.sh ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target( test_private
    DEPENDS  ca_private
    COMMAND  ${CMAKE_INSTALL_PREFIX}/ca_private 
    WORKING_DIRECTORY ${CMAKE_INSTALL_PREFIX}
    COMMENT "run generate code "
)

