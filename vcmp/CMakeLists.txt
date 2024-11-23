cmake_minimum_required(VERSION 3.10)
project(vcmp)

find_package(Libevent REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(spdlog REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_search_module(UUID REQUIRED uuid)

add_executable(vcmp main.cpp)
target_link_libraries(vcmp PRIVATE libevent::core OpenSSL::Crypto spdlog::spdlog ${UUID_LIBRARIES})