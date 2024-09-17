cmake_minimum_required(VERSION 3.29)
project(gate_server)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_TOOLCHAIN_FILE "E:/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(MYSQL_CONCPP_ROOT "E:/project/cpp/mysql-connector-c++-9.0.0-winx64")
set(MYSQL_CONCPP_LIBRARIES ${MYSQL_CONCPP_ROOT}/lib64/debug/vs14/mysqlcppconn.lib)

include_directories(${CMAKE_SOURCE_DIR}/public
        ${CMAKE_SOURCE_DIR}/proto
        "E:/project/cpp/boost_1_83_0"
        ${MYSQL_CONCPP_ROOT}/include)

link_directories("E:/project/cpp/boost_1_83_0/lib64-msvc-14.3")

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

find_package(nlohmann_json CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(unofficial-inih CONFIG REQUIRED)
find_package(redis++ CONFIG REQUIRED)

set(COMMON_LIBS
        redis++::redis++
        nlohmann_json::nlohmann_json
        spdlog::spdlog
        protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite
        gRPC::gpr gRPC::grpc gRPC::grpc++ gRPC::grpc++_alts
        unofficial::inih::inireader
        ${MYSQL_CONCPP_LIBRARIES}
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})


add_subdirectory(public)
add_subdirectory(gate-server)
add_subdirectory(status-server)
add_subdirectory(chat-server)
