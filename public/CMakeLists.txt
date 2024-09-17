project(public_tools)

add_library(public_tools SHARED
        inc.h
        singleton.h
        io_service_pool.cpp
        io_service_pool.h
        config_manager.h
        redis_connection_pool.cpp
        redis_connection_pool.h
        redis_manager.h
        mysql_connection_pool.cpp
        mysql_connection_pool.h
        mysql_dao.cpp
        mysql_dao.h
        mysql_manager.cpp
        mysql_manager.h
        grpc_connection_pool.h
)

target_link_libraries(public_tools PUBLIC ${COMMON_LIBS})

target_compile_definitions(public_tools PRIVATE PUBLIC_TOOLS_EXPORTS)

add_custom_command(TARGET public_tools POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/config.ini
        ${CMAKE_BINARY_DIR}
        COMMENT "Copying config.ini to executable directory"
)
