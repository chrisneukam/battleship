cmake_minimum_required (VERSION 2.6)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project (battleship)

include_directories("${PROJECT_SOURCE_DIR}/battleshipLib")

add_library(battleshipLib
  battleshipLib/ai.c
  battleshipLib/ai.h
  battleshipLib/battleshipLib.c
  battleshipLib/battleshipLib.h
  battleshipLib/position.c
  battleshipLib/position.h
  battleshipLib/randomGen.c
  battleshipLib/randomGen.h
  battleshipLib/ship.c
  battleshipLib/ship.h
  battleshipLib/util.c
  battleshipLib/util.h
)
set_target_properties (battleshipLib PROPERTIES
  FOLDER Libraries
)

add_executable(battleshipCmdl
  battleshipGame/battleshipCmdl.c
)
target_link_libraries(battleshipCmdl battleshipLib)
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
target_link_libraries(testGameCmdl battleshipLib)
set_target_properties (testGameCmdl PROPERTIES
  FOLDER Executables
)
