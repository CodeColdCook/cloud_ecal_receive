cmake_minimum_required(VERSION 3.0)

# set(CMAKE_FIND_PACKAGE_PREFER_CONFIG ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE "Debug" )
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb -pthread")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall -pthread")
add_definitions(-std=c++14)

## add protobuf
set(PROTO_GEN_CXX ON CACHE BOOL "enable CXX protobuf file generate")
set(PROTO_GEN_JAVA OFF CACHE BOOL "enable JAVA protobuf file generate")
set(PROTO_GEN_PYTHON OFF CACHE BOOL "enable PYTHON protobuf file generate")
add_subdirectory(external/cloud_protobuf) 

# include smiles mower protobuf dir 
get_property(CLOUD_PROTOBUF_INCLUDE_DIR GLOBAL PROPERTY "CLOUD_PROTOBUF_DIR" )
MESSAGE(STATUS "SMILES MOWER PROTOBUF_DIR :${CLOUD_PROTOBUF_INCLUDE_DIR}")
include_directories(${CLOUD_PROTOBUF_INCLUDE_DIR})


find_package(PCL REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})

add_executable(test_receive_ecal_cloud 
  src/main.cpp)
target_link_libraries(test_receive_ecal_cloud 
  ${PCL_LIBRARIES}
  cloud_protobuf
  )
