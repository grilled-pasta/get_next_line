# /bin/bash

for size in 1 2 7 42 1024
do
    cc -Wall -Wextra -Werror -D BUFFER_SIZE=$size \
        ../get_next_line.c ../get_next_line_utils.c test.c \
        -o test || break
    echo "BUFFER_SIZE=$size"
    ./test
done
