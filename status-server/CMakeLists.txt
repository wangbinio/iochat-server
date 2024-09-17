project(status_server)

add_executable(status_server
        ../proto/message.pb.h
        ../proto/message.pb.cc
        ../proto/message.grpc.pb.h
        ../proto/message.grpc.pb.cc
        status_server.cpp
        status_server_impl.cpp
        status_server_impl.h
)

target_link_libraries(status_server PRIVATE public_tools ${COMMON_LIBS})

add_custom_command(TARGET status_server POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/config.ini
        ${CMAKE_BINARY_DIR}
        COMMENT "Copying config.ini to executable directory"
)
