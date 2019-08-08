cmake_minimum_required(VERSION 3.13)
project(Wolf3D C)

set(CMAKE_C_STANDARD 99)

include_directories(libft /usr/local/lib)
include_directories(libft/include)
include_directories(include)
link_directories(libft /usr/local/lib)

set(SOURCE
        src/main.c
        src/init.c
        src/key_events.c
        src/draw.c
        src/read.c
        src/read2.c
        src/draw2.c
        src/texture.c)

add_executable(Wolf3D ${SOURCE})

target_link_libraries(Wolf3D -lmlx -lft "-framework OpenGL" "-framework AppKit")