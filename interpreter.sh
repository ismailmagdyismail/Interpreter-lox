export project_name=interpreter
export root_path=${PWD}
export src_path=${root_path}/src
export test_path=${root_path}/tests
export bin_path=${root_path}/bin

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
    cd ${bin_path}
    ./${project_name}
    cd ..
}

function makeClean(){
    cd build
    make clean
    cd ..
}
