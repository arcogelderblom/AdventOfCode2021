 #!/bin/bash

rm -rf _build
cmake -H. -B_build
cmake --build _build
./_build/$1/$1