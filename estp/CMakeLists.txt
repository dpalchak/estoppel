
add_subdirectory(base)
add_subdirectory(data)
add_subdirectory(platform)

if(ESTP_BUILD_TESTING)
    add_subdirectory(testing)
endif()