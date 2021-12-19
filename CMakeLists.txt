cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(21Z-EADS-TASK1-MILLER-ARTUR)

add_compile_options(-Wall -Wextra -pedantic -Werror)

include(FetchContent)

FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG main
)

FetchContent_Declare(
	Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG origin/devel
)
FetchContent_MakeAvailable(googletest)
FetchContent_MakeAvailable(Catch2)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC sequence)

target_link_libraries(${PROJECT_NAME} PUBLIC gtest_main)
target_link_libraries(${PROJECT_NAME} PUBLIC Catch2::Catch2WithMain)

