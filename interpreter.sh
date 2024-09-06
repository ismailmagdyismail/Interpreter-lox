export project_name=interpreter
export working_dir=${PWD}

export src_dir=src
export src_path=${working_dir}/${src_dir}

export test_dir=tests
export test_path=${working_dir}/${test_dir}

export bin_dir=bin
export bin_path=${working_dir}/${bin_dir}

export build_dir=build
export build_path=${working_dir}/${build_dir}

function init()
{
    mkdir ${build_dir} ${bin_dir}
}

function build()
{
    echo Building
    mkdir build
    cd build
    cmake ..
    make
    cd ..
    echo build finished
}

function run()
{
    build
    echo Running
    cd ${working_dir}
    ./${bin_dir}/${project_name}
    cd ${working_dir}
}

function makeClean()
{
    cd ${build_path}
    make clean
    cd ${working_dir}
}
