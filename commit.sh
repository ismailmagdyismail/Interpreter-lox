function enhance () {
    local commit_message=$1
    git commit -m "[Enhance]: ${commit_message}"
}


function fix() {
    local commit_message=$1
    git commit -m "[Fix]: ${commit_message}"
}


function feature() {
    local commit_message=$1
    git commit -m "[Feature]: ${commit_message}"
}


function get_logger()
{
    cd ${working_dir}

    rm -rf ${working_dir}/libs/

    mkdir ${working_dir}/libs
    mkdir ${lib_path}/includes
    mkdir ${lib_path}/includes/logger
    mkdir ${lib_path}/includes/debugger

    cp -r ../../logger/logger/include/*.hpp ${lib_path}/includes/logger
    cp ../../logger/logger/bin/liblogger.a ${lib_path}/
}
