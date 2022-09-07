project(Google_tests)
add_subdirectory(lib)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

include_directories(../include ${GTEST_INCLUDE_DIRS})

# adding the Google_Tests_run target
add_executable(Google_Tests_run
        ../src/ConverterJSON.cpp ../src/InvertredIndex.cpp ../src/fs_exception.cpp ../src/SearchServer.cpp
        jsonFilesTest.cpp ConverterJsonTest.cpp InvertedIndexTest.cpp SearchServerTest.cpp)

# linking Google_Tests_run with DateConverter_lib which will be tested
target_link_libraries(Google_Tests_run nlohmann_json::nlohmann_json)

target_link_libraries(Google_Tests_run gtest gtest_main)
