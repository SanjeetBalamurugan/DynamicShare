cmake_minimum_required(VERSION 3.16)
project(DynamicShareCore LANGUAGES CXX)

file(GLOB_RECURSE CORE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_library(DynamicShareCore SHARED ${CORE_SOURCES})

target_include_directories(DynamicShareCore
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/vendor/asio/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src	
)

message(STATUS "Source: ${CMAKE_SOURCE_DIR}")

target_compile_definitions(DynamicShareCore
    PRIVATE ASIO_STANDALONE
)

if(WIN32)
    target_compile_definitions(DynamicShareCore PRIVATE DYNAMICSHARECORE_EXPORTS)
    target_link_libraries(DynamicShareCore PRIVATE ws2_32)
endif()

target_compile_features(DynamicShareCore PUBLIC cxx_std_17)
