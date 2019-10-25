
add_estp_platform_libraries(host)

add_estp_platform_libraries(host32)

target_compile_options(host32_platform_build INTERFACE
    "-m32"
)

target_link_options(host32_platform_build INTERFACE
    "-m32"
)