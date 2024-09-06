cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(project_name $ENV{project_name})
set(working_dir $ENV{working_dir})
set(src_path $ENV{src_path})
set(bin_path $ENV{bin_path})
set(lib_path $ENV{lib_path})


project(${project_name})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${bin_path})

include_directories(${src_path})

add_executable(
    ${project_name}
    src/main.cpp
    src/sourceReader/FileReader.cpp
    src/sourceReader/ConsoleReader.cpp
)

target_link_libraries(${project_name} ${lib_path}/liblogger.a)
