cmake_minimum_required (VERSION 2.6)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project (battleship)

include_directories("${PROJECT_SOURCE_DIR}/battleshipGame")

add_library(batlleshipGameLib
  battleshipGame/ai.c
  battleshipGame/ai.h
  battleshipGame/position.c
  battleshipGame/position.h
  battleshipGame/randomGen.c
  battleshipGame/randomGen.h
  battleshipGame/ship.c
  battleshipGame/ship.h
  battleshipGame/util.c
  battleshipGame/util.h
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
  battleshipTest/testFramework.h
  battleshipTest/testGameCmdl.c
  battleshipTest/unittests.c
  battleshipTest/unittests.h
)
target_include_directories(testGameCmdl PRIVATE "${PROJECT_SOURCE_DIR}/battleshipTest")
target_link_libraries(testGameCmdl batlleshipGameLib)
set_target_properties (testGameCmdl PROPERTIES
  FOLDER Executables
)
