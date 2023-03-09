cmake_minimum_required(VERSION 3.10)

project(Server)

file(GLOB CPP_FILES
    ${PROJECT_SOURCE_DIR}/http/*.cpp
    ${PROJECT_SOURCE_DIR}/log/*.cpp
    ${PROJECT_SOURCE_DIR}/server/*.cpp
    ${PROJECT_SOURCE_DIR}/mysql/*.cpp
    ${PROJECT_SOURCE_DIR}/time/*.cpp
    )

set(CMAKE_CXX_STANDARD 11)

include_directories(
    ${PROJECT_SOURCE_DIR}/log 
    ${PROJECT_SOURCE_DIR}/tcp 
    ${PROJECT_SOURCE_DIR}/thread 
    ${PROJECT_SOURCE_DIR}/utils 
    ${PROJECT_SOURCE_DIR}/server 
    ${PROJECT_SOURCE_DIR}/http 
    ${PROJECT_SOURCE_DIR}/mysql
    ${PROJECT_SOURCE_DIR}/time)

add_executable(server main.cpp ${CPP_FILES})

target_link_libraries(server pthread mysqlclient)