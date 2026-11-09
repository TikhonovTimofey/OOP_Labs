cmake_minimum_required(VERSION 3.25)
project(lab1_trie)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=-*,cppcoreguidelines-*")

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_executable(lab1_trie
        main.cpp
        trie.cpp
        trie.h
        node_t.cpp
        node_t.h
        test_trie.cpp
)


target_link_libraries(lab1_trie PRIVATE gtest gtest_main)


enable_testing()
include(GoogleTest)
gtest_discover_tests(lab1_trie)