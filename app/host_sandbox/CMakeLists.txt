
project(Host_Sandbox C CXX)

estp_add_executable(
    NAME
        host_sandbox
    ARCH
        host32
    SOURCES
        main.cc
    DEFINES
        PRIVATE SPECIAL_MESSAGE=\"Greetings\ from\ nowhere\"
)
