include_directories("${PROJECT_SOURCE_DIR}/src")
link_directories(${PROJECT_BINARY_DIR}/lib)

add_subdirectory(nmode)
add_subdirectory(binaries)
add_subdirectory(exp)

