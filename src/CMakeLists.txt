include_directories("${PROJECT_SOURCE_DIR}/src")
link_directories(${PROJECT_BINARY_DIR}/lib)

add_subdirectory(base)
add_subdirectory(evo)

# add_subdirectory(binaries)
