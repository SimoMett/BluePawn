cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_compile_definitions(GTESTING)
set(SOURCE_FILES runAllTests.cpp ../ConfigFile.h ../ConfigFile.cpp TestConfigFile.cpp)

add_executable(allBluePawnTests ${SOURCE_FILES})

target_link_libraries(allBluePawnTests ${GTEST_BOTH_LIBRARIES} stdc++fs)