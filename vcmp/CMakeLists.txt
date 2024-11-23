cmake_minimum_required(VERSION 3.10)
project(vcmp)
set(CMAKE_CXX_STANDARD 11)

find_package(Libevent REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(spdlog REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_search_module(UUID REQUIRED uuid)

add_executable(vcmp main.cpp src/vcmp/peer_server.cpp src/vcmp/ws_server.cpp)
target_include_directories(vcmp PUBLIC include lib ${UUID_INCLUDE_DIRS})
target_link_libraries(vcmp PRIVATE libevent::core OpenSSL::Crypto spdlog::spdlog ${UUID_LIBRARIES})

add_custom_target(copy_config ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/config.json ${CMAKE_BINARY_DIR}/config.json
    COMMENT "Copying config to build directory"
)
add_dependencies(vcmp copy_config)