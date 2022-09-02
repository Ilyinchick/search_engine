cmake_minimum_required(VERSION 3.21)

add_executable(search_engine main.cpp ConverterJSON.cpp fs_exception.cpp InvertredIndex.cpp SearchServer.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${MY_VAR})