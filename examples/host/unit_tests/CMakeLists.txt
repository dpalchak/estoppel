CMAKE_MINIMUM_REQUIRED(VERSION 3.13)

set(ESTP_PLATFORM host)
set(ESTP_BUILD_TESTING ON)

include("estoppel/cmake/estp_app.cmake")

project(HostTests)
