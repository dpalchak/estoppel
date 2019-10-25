CMAKE_MINIMUM_REQUIRED(VERSION 3.13)

set(ESTP_PLATFORM host)
set(ESTP_BUILD_TESTING ON)

include("estoppel/cmake/estp_app.cmake")

project(HelloWorld)

add_estp_executable(hello_world
    main.cc
)

target_compile_definitions(hello_world PRIVATE
    SPECIAL_MESSAGE=\"Greetings\ from\ nowhere\"
)