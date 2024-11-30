cmake_minimum_required (VERSION 3.5)

project (Compound)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  bin)

set(CMAKE_C_COMPILER  clang)

add_compile_options(-g -std=c99 -Wall -Wextra -D__DEBUG__)

set(SHARED_SOURCE
  src/array.c
  src/catlog.c
  # src/class.c
  # src/class_register.c
  # src/format.c
  src/memory.c
  src/memory_stack.c
  src/stack.c
  src/status.c
  src/status_stack.c
  src/type.c
)

set(LIBCOMPOUND_SOURCE ${SHARED_SOURCE})

add_library(compound SHARED ${LIBCOMPOUND_SOURCE})

add_executable(CompoundTest
               ${SHARED_SOURCE}
               test.c)
