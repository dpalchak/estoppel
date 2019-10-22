CMAKE_MINIMUM_REQUIRED(VERSION 3.13)

project(hello_world C CXX)

include(CTest)
enable_testing()

add_subdirectory(estoppel)

estp_add_executable(
    NAME
        hello_world
    ARCH
        host
    SOURCES
        main.cc
    DEFINES
        PRIVATE SPECIAL_MESSAGE=\"Greetings\ from\ nowhere\"
)
