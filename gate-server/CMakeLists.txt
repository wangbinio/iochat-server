project(gate_server)

add_executable(gate_server
        gate_server.cpp
        http_connection.cpp
        http_connection.h
        server.cpp
        server.h
        verify_grpc_client.cpp
        verify_grpc_client.h
        status_grpc_client.cpp
        status_grpc_client.h
        logic_system.cpp
        logic_system.h

        ../proto/message.pb.h
        ../proto/message.pb.cc
        ../proto/message.grpc.pb.h
        ../proto/message.grpc.pb.cc
)

target_link_libraries(gate_server PRIVATE public_tools ${COMMON_LIBS})

add_custom_command(TARGET gate_server POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/config.ini
        ${CMAKE_BINARY_DIR}
        COMMENT "Copying config.ini to executable directory"
)
