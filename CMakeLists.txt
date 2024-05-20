cmake_minimum_required(VERSION 3.5)
project(MyProject)

# Add executable
add_executable(main main.c
    nano_protobuf/pb_common.c
    nano_protobuf/pb_decode.c
    nano_protobuf/pb_encode.c
    protobuf_zigbee/zigbee.pb.c
)

# Add include directories
target_include_directories(main PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/nano_protobuf
    ${CMAKE_CURRENT_SOURCE_DIR}/protobuf_zigbee
)
