cmake_minimum_required(VERSION 3.10)
project(inter_process_com LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(
    include
)

add_library(ipc_server src/ipc/unix_sockets/ipc_server.cpp)
add_library(ipc_client src/ipc/unix_sockets/ipc_client.cpp)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} ipc_server ipc_client)
