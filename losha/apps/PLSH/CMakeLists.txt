include_directories(${PROJECT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../lshcore)

if(LIBHDFS3_FOUND)
    include_directories(${LIBHDFS3_INCLUDE_DIR})
    add_definitions(-DWITH_HDFS)
else(LIBHDFS3_FOUND)
    add_definitions(-DWITHOUT_HDFS)
endif(LIBHDFS3_FOUND)

### applications
set(husky husky-lib husky-io husky-core husky-base)
add_executable(PLSH plsh.cpp )
target_link_libraries(PLSH ${husky})
target_link_libraries(PLSH ${EXTERNAL_LIB})
husky_default_properties(PLSH)

### test
set(husky husky-io husky-core husky-lib)
add_executable(TestPLSH testplsh.cpp )
target_link_libraries(TestPLSH ${husky})
target_link_libraries(TestPLSH ${EXTERNAL_LIB})
