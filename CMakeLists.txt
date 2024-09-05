cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(project_name $ENV{project_name})
set(src_path $ENV{src_path})
set(root_path $ENV{root_path})
set(bin_path $ENV{bin_path})


project(${project_name})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${bin_path})

include_directories(${src_path})

add_executable(
    ${project_name}
    src/main.cpp
    src/sourceReader/FileReader.cpp
    src/sourceReader/ConsoleReader.cpp
    src/logger/ILogger.cpp
    src/logger/ConsoleLogger.cpp
    src/logger/FileLogger.cpp
)
