file(GLOB_RECURSE LIBCSC_SOURCE_FILES 
		${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

file(GLOB_RECURSE LIBCSC_HEADER_FILES 
		${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

add_library(libcsc ${LIBCSC_SOURCE_FILES} ${LIBCSC_HEADER_FILES})
set_compile_options(libcsc)
target_include_directories(libcsc PRIVATE ./)