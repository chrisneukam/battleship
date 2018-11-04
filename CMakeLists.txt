cmake_minimum_required (VERSION 2.6)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project (battleship)

include_directories("${PROJECT_SOURCE_DIR}/battleshipGame")

add_library(batlleshipGameLib
  battleshipGame/ship.c
  battleshipGame/ai.c
  battleshipGame/randomGen.c
)
set_target_properties (batlleshipGameLib PROPERTIES
  FOLDER Libraries
)

add_executable(battleshipCmdl
  battleshipGame/battleshipCmdl.c
)
target_link_libraries(battleshipCmdl batlleshipGameLib)
set_target_properties (battleshipCmdl PROPERTIES
  FOLDER Executables
)

add_executable(testGameCmdl
  battleshipTest/testFramework.c
  battleshipTest/testGameCmdl.c
  battleshipTest/unittests.c
)
target_include_directories(testGameCmdl PRIVATE "${PROJECT_SOURCE_DIR}/battleshipTest")
target_link_libraries(testGameCmdl batlleshipGameLib)
set_target_properties (testGameCmdl PROPERTIES
  FOLDER Executables
)
