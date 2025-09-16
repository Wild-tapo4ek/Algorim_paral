cmake_minimum_required(VERSION 3.14)
project(MyGTestProject)

# Настройка C++ стандарта
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Поиск пакета gtest
find_package(GTest REQUIRED)

# Проверка существования исходного файла
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/test_fun.cpp)
    add_executable(test_runner test_fun.cpp)
    target_link_libraries(test_runner PRIVATE GTest::gtest GTest::gtest_main)
    message(STATUS "Test executable 'test_runner' will be built")
else()
    message(WARNING "File test_fun.cpp not found - skipping test_runner target")
endif()