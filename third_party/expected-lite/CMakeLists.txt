# estp_add_interface_library(
#     NAME
#         expected-lite
#     INCLUDE_DIRS
#         upstream/include
# )

add_estp_library(expected-lite INTERFACE)
target_include_directories(expected-lite INTERFACE upstream/include)
