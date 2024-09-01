cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(project_name $ENV{project_name})
set(src_path $ENV{src_path})

project(${project_name})

include_directories(${src_path})

add_executable(
    ${project_name}
    src/main.cpp
    src/sourceReader/FileReader.cpp
    src/sourceReader/ConsoleReader.cpp
)
