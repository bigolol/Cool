cmake_minimum_required(VERSION 3.7)
project(Cool)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp SortedVector.h CooTensorElement.h CooTensor.h CsfTensor.h typedefs.h)
add_executable(Cool ${SOURCE_FILES})

FIND_PACKAGE( OpenMP REQUIRED)
if(OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()