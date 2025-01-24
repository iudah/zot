cmake_minimum_required(VERSION 3.15)

project(Zot VERSION 1.0 DESCRIPTION "zot memory manager")

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

# Install targets
install(TARGETS ${TARGET} DESTINATION lib)
install(FILES ${HEADER_FILES} DESTINATION include)
