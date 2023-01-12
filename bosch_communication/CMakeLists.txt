cmake_minimum_required(VERSION 3.5)

project(bosch_communication LANGUAGES CXX)

add_library(${PROJECT_NAME}
    "include/bosch_communicator.hpp"
    "include/converter_interface.hpp"
    "include/bosch_protocol.hpp"
	"include/tcp_server.hpp"

    "src/bosch_protocol.cpp"
    # "src/bosch_converter_interface.cpp"
    "src/bosch_communicator.cpp"
	"src/tcp_server.cpp"
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>

    PRIVATE
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
	boost::system
    boost::headers
)