CMAKE_MINIMUM_REQUIRED(VERSION 3.13)

set(ESTP_PLATFORM stm32l4x6xg)

include("estoppel/cmake/estp_app.cmake")

project(HelloWorld)

add_estp_executable(hello_world
    main.cc
)

target_link_options(hello_world PRIVATE
    --specs=nano.specs       # use minimal newlib config
    --specs=nosys.specs      # use empty syscalls
)
