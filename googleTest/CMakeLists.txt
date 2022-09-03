project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# adding the Google_Tests_run target
add_executable(Google_Tests_run ConverterJsonTest.cpp ../src/ConverterJSON.cpp ../src/fs_exception.cpp ../src/InvertredIndex.cpp jsonFilesTest.cpp
        InvertedIndexTest.cpp ../src/SearchServer.cpp SearchServerTest.cpp)

# linking Google_Tests_run with DateConverter_lib which will be tested
target_link_libraries(Google_Tests_run nlohmann_json::nlohmann_json)

target_link_libraries(Google_Tests_run gtest gtest_main)