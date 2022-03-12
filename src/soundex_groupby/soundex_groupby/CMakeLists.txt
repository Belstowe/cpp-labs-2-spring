file(GLOB_RECURSE SOUNDEX_GROUPBY_SOURCE_FILES 
		${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

file(GLOB_RECURSE SOUNDEX_GROUPBY_HEADER_FILES 
		${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

add_executable(soundex_groupby ${SOUNDEX_GROUPBY_SOURCE_FILES} ${SOUNDEX_GROUPBY_HEADER_FILES})
set_compile_options(soundex_groupby)
target_include_directories(soundex_groupby PRIVATE ./)
target_link_libraries(soundex_groupby PRIVATE libcsc CLI11 rapidcsv nlohmann_json::nlohmann_json)

configure_file("${CMAKE_SOURCE_DIR}/assets/names2020.csv" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/" COPYONLY)