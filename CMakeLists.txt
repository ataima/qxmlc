cmake_minimum_required (VERSION 2.8.11)
project (qxmlc)
set(CXX_STANDARD 14)
set(CXX_STANDARD_REQUIRED YES)
set(CXX_EXTENSIONS NO)

add_subdirectory (./ca_packfile)
add_subdirectory (./ca_logger)
add_subdirectory (./ca_libxmlca)
add_subdirectory (./ca_test)
add_subdirectory (./ca_qxmlc)

add_subdirectory (./ca_private)
add_subdirectory (./ca_xmlsh)

