##################################################################
# Variables
##################################################################

cmake_minimum_required(VERSION 3.16)
project(
  aurix-sample
  DESCRIPTION "Aurix code example Flash_Programming_1_KIT_TC334_LK converted to CMake"
  LANGUAGES C CXX
)

##################################################################
# Build configuration
##################################################################

add_subdirectory(third_party)
add_subdirectory(src)

