project(nslookup)

file(GLOB SRC src/*.cpp src/*.cxx)
add_executable(${PROJECT_NAME} ${SRC} src/nslookup.cpp)

target_link_libraries(${PROJECT_NAME} ${COMMON_DEPENDENCIES})
