cmake_minimum_required(VERSION 3.15)

project(Zot VERSION 2.1 DESCRIPTION "zot memory manager")

set(TARGET zot)

# Set C standard
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Define compiler warnings in one place
set(C_WARNINGS "-Wall -Wextra -Wshadow -Wformat=2 -Wunused")

# Set flags for Debug and Release configurations
set(CMAKE_C_FLAGS_DEBUG     "${CMAKE_C_FLAGS_DEBUG} -ggdb3 -O0 -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_C_FLAGS_RELEASE   "${CMAKE_C_FLAGS_RELEASE} -O3")

set(HEADER_FILES include/zot.h)
set(SOURCE_FILES src/zot.c)

include(ExternalProject)

ExternalProject_Add(
  MemAlloc
  SOURCE_DIR /sdcard/Jay/Projects/xab_laud_ubject/memalloc/
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/memalloc -BUILD_EXE=OFF
  BUILD_ALWAYS TRUE
  BUILD_BYPRODUCTS ${CMAKE_BINARY_DIR}/memalloc/lib/libmemalloc.a
)

# Create INTERFACE target for shared flags
add_library(zot_c_flags INTERFACE)
target_compile_features(zot_c_flags INTERFACE c_std_17)
target_compile_options(
  zot_c_flags
  INTERFACE
    "$<BUILD_INTERFACE:${C_WARNINGS}>"
)

# Main library setup
add_library(${TARGET} SHARED)
target_sources(${TARGET} PRIVATE ${SOURCE_FILES})
target_include_directories(${TARGET} PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/memalloc/include)
target_link_directories(${TARGET} PRIVATE ${CMAKE_BINARY_DIR}/memalloc/lib/)
target_link_libraries(${TARGET} PRIVATE memalloc)
add_dependencies(${TARGET} MemAlloc)

# Install targets
install(TARGETS ${TARGET} DESTINATION lib)
install(FILES ${HEADER_FILES} DESTINATION include)
