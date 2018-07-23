cmake_minimum_required( VERSION 3.5 )

project(expected-lite LANGUAGES CXX )

estp_add_interface_library(
    NAME
        expected-lite
    INCLUDE_DIRS
        upstream/include
)
