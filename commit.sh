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
