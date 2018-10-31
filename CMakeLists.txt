cmake_minimum_required (VERSION 2.6)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project (battleship)

include_directories("${PROJECT_SOURCE_DIR}/battleshipGame")

add_executable(battleshipCmdl
  battleshipGame/battleshipCmdl.c
  battleshipGame/ship.c
  battleshipGame/ai.c
)
set_target_properties (battleshipCmdl PROPERTIES
  FOLDER Executables
)

add_executable(testGameCmdl
  battleshipTest/testGameCmdl.c
  battleshipGame/ship.c
  battleshipGame/ai.c
)
set_target_properties (testGameCmdl PROPERTIES
  FOLDER Executables
)
