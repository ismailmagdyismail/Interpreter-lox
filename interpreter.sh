export project_name=interpreter
export base_path=${PWD}
export src_path=${base_path}/src
export test_path=${base_path}/tests

function build(){
    echo Building
    mkdir build
    cd build
    cmake ..
    make
    cd ..
    echo build finished
}

function run(){
    build
    echo Running
    cd build
    ./${project_name}
    cd ..
}

function makeClean(){
    cd build
    make clean
    cd ..
}
