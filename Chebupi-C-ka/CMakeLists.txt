#------------------------------------------------------------------------------
#
# Source code for MIPT ILab
# Slides: https://sourceforge.net/projects/cpp-lects-rus/files/cpp-graduate/
# Licensed after GNU GPL v3
#
#------------------------------------------------------------------------------
#
#  cmake for simplest grammar example
#  default: cmake -DCMAKE_BUILD_TYPE=Release -DGRAMMAR="numgrammar-sr.y" ..
#      try: cmake -DCMAKE_BUILD_TYPE=Release -DGRAMMAR="numgrammar-sr-fixed.y" ..
#      try: cmake -DCMAKE_BUILD_TYPE=Release -DGRAMMAR="numgrammar.y" ..
#
#-----------------------------------------------------------------------------


cmake_minimum_required(VERSION 3.13.4)
project(Chebupi-C-ka)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

flex_target(scanner
  lexer.l
  ${CMAKE_CURRENT_BINARY_DIR}/lexer.cc
)

bison_target(parser
  grammar.y
  ${CMAKE_CURRENT_BINARY_DIR}/parser.cc
  COMPILE_FLAGS "-Wconflicts-rr -Wconflicts-sr -Wcounterexamples --defines=${CMAKE_CURRENT_BINARY_DIR}/grammar.tab.hh")

add_flex_bison_dependency(scanner parser)

add_executable(${PROJECT_NAME} 
  driver.cpp 
  ${BISON_parser_OUTPUTS}
  ${FLEX_scanner_OUTPUTS}
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})