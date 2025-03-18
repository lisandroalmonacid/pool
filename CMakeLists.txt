cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(PoolGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g -march=x86-64 -mtune=generic")

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.h)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    src
)

add_executable(Pool ${SOURCES} ${HEADERS})

# target_link_libraries(Pool
#     ${SDL2_LIBRARIES}
#     ${SDL2_IMAGE_LIBRARIES}
#     ${SDL2_TTF_LIBRARIES}
# )

target_link_libraries(Pool
    -lSDL2
    -lSDL2main
    -lSDL2_image
    -lSDL2_ttf
)
