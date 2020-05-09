cmake_minimum_required(VERSION 3.14)
# 'MyUnits' is the subproject name
project(MyUnits)

set(CMAKE_CXX_STANDARD 17)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib/googletest ../src)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../src)
include_directories(/Users/anton/Programming/CLionProjects/ACS/acs-spring-l2/src)

# 'Google_Tests_run' is the target name
# 'AllTestsForDecoder.cpp AllTestsForExecuter.cpp' are source files with tests
# adding the Google_Tests_run target
add_executable(Google_Tests_run
        Tests/AllTestsForDecoder.cpp
        Tests/AllTestsForExecuter.cpp)

target_link_libraries(Google_Tests_run gtest gtest_main)