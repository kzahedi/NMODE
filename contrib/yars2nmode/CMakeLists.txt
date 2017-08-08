project(yars2nmode Go)

set(SOURCE_FILES yars2nmode.go)
set(CMAKE_Go_COMPILER "/usr/local/bin/go")

add_executable(yars2nmode ${SOURCE_FILES})
