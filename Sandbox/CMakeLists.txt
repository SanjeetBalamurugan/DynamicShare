cmake_minimum_required(VERSION 3.16)
project(Sandbox LANGUAGES CXX)

add_executable(Sandbox "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

target_link_libraries(Sandbox
    PRIVATE
        DynamicShareCore
	ws2_32
)

target_compile_features(Sandbox PUBLIC cxx_std_17)

set_target_properties(Sandbox PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

set_target_properties(DynamicShareCore PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
