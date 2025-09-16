cmake_minimum_required(VERSION 3.14)
project(Parallel_prog_lab1)

# Включить модуль FetchContent
include(FetchContent)

# Задать настройки для GoogleTest
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)

# Сделать GoogleTest доступным
FetchContent_MakeAvailable(googletest)

# Создать исполняемый файл для тестов
add_executable(run_tests 1.cpp)

# Добавить include-директории GoogleTest
target_include_directories(run_tests PRIVATE 
    ${googletest_SOURCE_DIR}/googletest/include
    ${googletest_SOURCE_DIR}/googlemock/include
)

# Подключить GoogleTest к нашему проекту
target_link_libraries(run_tests gtest_main)

# Включить стандарт C++17
set_target_properties(run_tests PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)