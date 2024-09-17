project(chat_server)

add_executable(chat_server
        ../proto/message.pb.h
        ../proto/message.pb.cc
        ../proto/message.grpc.pb.h
        ../proto/message.grpc.pb.cc
        chat_server.cpp

)

target_link_libraries(chat_server PRIVATE public_tools ${COMMON_LIBS})

add_custom_command(TARGET chat_server POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/config.ini
        ${CMAKE_BINARY_DIR}
        COMMENT "Copying config.ini to executable directory"
)
