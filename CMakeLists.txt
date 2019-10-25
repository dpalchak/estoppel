cmake_minimum_required(VERSION 3.13)



if(NOT (ESTP_ROOT AND ESTP_PLATFORM))
    message(FATAL_ERROR
        "Estoppel appears to have been added to this build via add_subdirectory(...)"
        "Please use"
        "\tinclude(./path/to/estp_project.cmake)"
        "\testp_project($NAME $PLATFORM)"
        "instead."
    )
endif()

# Create Estoppel subproject
project("Estoppel")

add_subdirectory(third_party EXCLUDE_FROM_ALL)
add_subdirectory(estp)

