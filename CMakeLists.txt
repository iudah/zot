cmake_minimum_required(VERSION 3.15)

project(Zot VERSION 2.1 DESCRIPTION "zot memory manager")

set(TARGET zot)

# Set C standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Define compiler warnings in one place
set(C_WARNINGS "-Wall -Wextra -Wshadow -Wformat=2 -Wunused")

# Set flags for Debug and Release configurations
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -ggdb3 -O0 -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")

set(HEADER_FILES include/zot.h)
set(SOURCE_FILES src/zot.c)

include(ExternalProject)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}/memalloc/lib/cmake/memalloc")
message(STATUS "memalloc will search in ${CMAKE_PREFIX_PATH}")
find_package(memalloc QUIET)
if(NOT memalloc_FOUND)
  ExternalProject_Add(
    MemAlloc
    GIT_REPOSITORY  "https://github.com/iudah/memalloc.git"
    GIT_TAG 79e9651
#    SOURCE_DIR /sdcard/Jay/Projects/xab_laud_ubject/memalloc/
    INSTALL_DIR ${CMAKE_BINARY_DIR}/memalloc
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR> -DBUILD_EXEC=OFF
    BUILD_ALWAYS OFF
    STAMP_DIR ${CMAKE_BINARY_DIR}/stamps
    UPDATE_DISCONNECTED TRUE
  )
else()
  message(STATUS "memalloc was found in ${CMAKE_PREFIX_PATH}")
endif()
message(STATUS "memalloc was found: ${memalloc_FOUND}")


# Create INTERFACE target for shared flags
add_library(zot_c_flags INTERFACE)
target_compile_features(zot_c_flags INTERFACE c_std_17)
target_compile_options(
  zot_c_flags
  INTERFACE
  "$<BUILD_INTERFACE:${C_WARNINGS}>"
)

# Main library setup
add_library(${TARGET} STATIC)
target_sources(${TARGET} PRIVATE ${SOURCE_FILES})
target_include_directories(${TARGET} PRIVATE include)
target_link_libraries(${TARGET} PUBLIC memalloc)
if(NOT memalloc_FOUND)
  target_include_directories(${TARGET} PRIVATE ${CMAKE_BINARY_DIR}/memalloc/include)
  add_dependencies(${TARGET} MemAlloc)
endif()


# Install targets
install(TARGETS ${TARGET} EXPORT ZotTargets LIBRARY DESTINATION lib INCLUDES DESTINATION include)
install(FILES ${HEADER_FILES} DESTINATION include)
install(EXPORT ZotTargets FILE zot-config.cmake DESTINATION lib/cmake/zot)

# Install beacon
export(EXPORT ZotTargets FILE "${CMAKE_BINARY_DIR}/zot-config.cmake")
