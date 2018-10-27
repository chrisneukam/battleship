cmake_minimum_required (VERSION 2.6)

project (battleship)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(battleship
  src/battleship.c
  src/ship.c
)
