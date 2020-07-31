cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# set the project name
project( genomes )

# set debugging
set(CMAKE_BUILD_TYPE Debug)

# include source
get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
include_directories(${PARENT_DIR}/Tools)

# Optionally you can use file glob (uncomment the next line)
file( GLOB_RECURSE GENOME_SOURCES *.cpp )
add_library( genomes ${GENOME_SOURCES})


