cmake_minimum_required(VERSION 3.18.4)

project(

  MpiPlayground
  VERSION 0.0.0.1
  DESCRIPTION "Project for learning how to openmpi"
  LANGUAGES CXX Fortran C

  )

include(FetchContent)

find_package(MPI REQUIRED COMPONENTS CXX)
if(MPI_CXX_FOUND)

else(MPI_CXX_FOUND)
  message(SEND_ERROR "MPI not found")
endif(MPI_CXX_FOUND)

set(CMAKE_VERBOSE_MAKEFILE "ON" CACHE STRING "" FORCE)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib CACHE STRING "" FORCE)
set(CMAKE_BUILD_RPATH /home/kmdetullio/working/Boost/boost/stage/lib)

add_definitions(-DGLOBAL_LOG_ENABLED -DREENTRANT -DBOOST_ERROR_CODE_HEADER_ONLY -DBOOST_LOG_DYN_LINK -DBOOST_ENABLE_ASSERT_HANDLER -DBOOST_SYSTEM_NO_DEPRECATED)

add_compile_options(-std=c++2a -isystem)
add_compile_options(-Wall -Wswitch -Wdeprecated-declarations -Wempty-body -Wconversion -Wreturn-type -Wparentheses -Wformat -Wuninitialized -Wunreachable-code -Wunused-function -Wunused-value -Wunused-variable)
add_compile_options(-fstrict-aliasing -fno-omit-frame-pointer -fthreadsafe-statics -fexceptions -frtti)

add_compile_options(-ggdb3)

add_executable(MpiPrimaryExecutive Driver.cpp Logger.cpp Assertions.cpp)

include_directories(SYSTEM ${MPI_CXX_INCLUDE_DIRS} /home/kmdetullio/working/Boost/boost)
target_link_directories(MpiPrimaryExecutive PUBLIC ${MPI_CXX_LINK_DIRS} /home/kmdetullio/working/Boost/boost/stage/lib)
target_link_libraries(MpiPrimaryExecutive PUBLIC ${MPI_CXX_LIBRARIES} boost_log boost_log_setup boost_thread boost_filesystem rt dl stdc++fs)

set_target_properties(MpiPrimaryExecutive PROPERTIES COMPILE_FLAGS "${MPI_CXX_COMPILE_FLAGS}")
set_target_properties(MpiPrimaryExecutive PROPERTIES LINK_FLAGS "${MPI_CXX_LINK_FLAGS}")


