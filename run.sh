export project_name=interpreter

function build(){
    echo Building
    mkdir build
    cd build
    cmake ..
    make
    cd ..
    echo build finished successfully
}

function run(){
    build
    echo Running
    cd build
    ./${project_name}
    cd ..
}
