cmake_minimum_required(VERSION 3.21)
project(search_engine)

set(CMAKE_CXX_STANDARD 17)
set(MY_VAR ${CMAKE_SOURCE_DIR}/include)
set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(json-develop)

add_subdirectory(src)

target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)

add_subdirectory(googleTest)