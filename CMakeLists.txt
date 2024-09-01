set(project_name $ENV{project_name})
project(${project_name})

include_directories(${CMAKE_DIR}/src)

add_executable(
    ${project_name}
    src/main.cpp
)
