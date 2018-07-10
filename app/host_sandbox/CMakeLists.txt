
if(NOT ${ARCH_TYPE_HOST})
    return()
endif()

project(Host_Sandbox)

add_executable(host_sandbox
    main.cc
)

target_compile_definitions(host_sandbox PRIVATE
    "SPECIAL_MESSAGE=\"Greetings\ from\ nowhere\""
)