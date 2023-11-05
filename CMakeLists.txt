cmake_minimum_required(VERSION 3.25)
project(alpha1)

set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SHARED_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shared)

add_compile_options(-frtti -fexceptions)
add_compile_options(-O3)

MACRO(RECURSE_FILES return_list filter)
    FILE(GLOB_RECURSE new_list ${filter})
    SET(file_list "")
    FOREACH(file_path ${new_list})
        SET(file_list ${file_list} ${file_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES file_list)
    SET(${return_list} ${file_list})
ENDMACRO()

RECURSE_FILES(cpp_file_list ${SOURCE_DIR}/*.cpp)
RECURSE_FILES(c_file_list ${SOURCE_DIR}/*.c)

add_library(
        alpha1
        SHARED
        ${cpp_file_list}
        ${c_file_list}
)

target_include_directories(alpha1 PRIVATE .)
target_include_directories(alpha1 PRIVATE ${SOURCE_DIR})
target_include_directories(alpha1 PRIVATE ${INCLUDE_DIR})
target_include_directories(alpha1 PUBLIC ${SHARED_DIR})
