cmake_minimum_required(VERSION 3.16)

project(matrix)

set(CMAKE_CXX_STANDARD 20)

# collecting libs
#add_subdirectory(lib)
# message(STATUS "Collected libs: ${LIBLIST}")

# foreach(LIB ${LIBLIST})
#   target_include_directories(${LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/${LIB})
#   target_include_directories(${LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
# endforeach()

set(SRCS
  src/main.cpp
)
set(EXEC_FILE "calc_det")

add_executable(${EXEC_FILE} ${SRCS})


add_library(matrix INTERFACE)
target_include_directories(
    matrix
    INTERFACE
        $<BUILD_INTERFACE:${EnTT_SOURCE_DIR}/lib>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

#target_include_directories(${EXEC_FILE} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories (${EXEC_FILE} PRIVATE ${CMAKE_SOURCE_DIR}/lib/)
#target_link_libraries(${EXEC_FILE} ${LIBLIST})
#target_include_directories(${EXEC_FILE} PRIVATE ${CMAKE_BINARY_DIR})


option(WITH_TESTS OFF)
if (WITH_TESTS)
  message("building with google tests")
  enable_testing()
  add_subdirectory(test)
endif()
