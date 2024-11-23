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

# include paths
include_directories(${src_path})

# paths for external libraries
include_directories(${lib_path}/includes)

# build version
set(CMAKE_BUILD_TYPE Debug)


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
    ${src_path}/lox.cpp
    ${src_path}/parser/Parser.cpp
    ${src_path}/expressions/BinaryExpression.cpp
    ${src_path}/expressions/UnaryExpression.cpp
    ${src_path}/expressions/LiteralExpression.cpp
    ${src_path}/expressions/GroupedExpression.cpp
    ${src_path}/expressions/TernaryExpression.cpp
    ${src_path}/expressions/VariableExpression.cpp
    ${src_path}/expressions/AssignmentExpression.cpp
    ${src_path}/expressionsFormatter/ExpressionPrinter.cpp
    ${src_path}/statements/ExpressionStatement.cpp
    ${src_path}/statements/PrintStatement.cpp
    ${src_path}/statements/VarStatement.cpp
    ${src_path}/statements/BlockStatement.cpp
    ${src_path}/statements/IfStatement.cpp
    ${src_path}/statements/WhileStatement.cpp
    ${src_path}/statements/ForStatement.cpp
    ${src_path}/stringBuilder/StringBuilder.cpp
    ${src_path}/object/Object.cpp
    ${src_path}/interpreter/Interpreter.cpp
    ${src_path}/enviroment/Enviroment.cpp
    ${src_path}/enviroment/EnviromentManager.cpp
)



# libraries to link against
target_link_libraries(${project_name} ${lib_path}/liblogger.a)
