cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(project_name $ENV{project_name})
set(working_dir $ENV{working_dir})
set(src_path $ENV{src_path})
set(bin_path $ENV{bin_path})
set(lib_path $ENV{lib_path})


project(${project_name})

# output binaries path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${bin_path})

# source paths
include_directories(${src_path})
# paths for external libraries
include_directories(${lib_path}/includes)


add_executable(
    ${project_name}
    ${src_path}/main.cpp
    ${src_path}/sourceReader/FileReader.cpp
    ${src_path}/sourceReader/ConsoleReader.cpp
    ${src_path}/lexer/Lexer.cpp
    ${src_path}/tokens/Token.cpp
    ${src_path}/sourceReporter/IReportMessage.cpp
    ${src_path}/sourceReporter/LineDescriptor.cpp
    ${src_path}/sourceReporter/LineError.cpp
    ${src_path}/sourceReporter/SourceReporter.cpp
)



# libraries to link against
target_link_libraries(${project_name} ${lib_path}/liblogger.a)
