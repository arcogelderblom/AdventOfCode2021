 #!/bin/bash

rm -rf _build
cmake -H. -B_build
cmake --build _build
for files in "_build/Day*/Day*"
do
    for file in $files
    do
        echo $file
        ./$file
    done
done