project(practice03_tcp_select_echo_client)

include_directories(include)
file(GLOB SRC src/*.cpp src/*.cxx)
add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} ${COMMON_DEPENDENCIES})
