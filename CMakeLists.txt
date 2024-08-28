cmake_minimum_required (VERSION 3.5)

project (Compound)

set(CMAKE_C_COMPILER  clang)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  out)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  out)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  out)

add_compile_options(-g -std=c99 -Wall -Wextra -D__DEBUG__)

# set(SHARED_SOURCE)

# set(LIBCOMPOUND_SOURCE ${SHARED_SOURCE})

# add_library(compound SHARED ${LIBCOMPOUND_SOURCE})

# LINK_LIBRARIES(m)

add_executable(CompoundTest
               ${SHARED_SOURCE}
               test.c)
