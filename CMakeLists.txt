cmake_minimum_required(VERSION 3.5)

project(asio_server VERSION 0.5.0.0)

# bushido packages
set(init_bushido "${CMAKE_BINARY_DIR}/.bushido-init.cmake")
execute_process(COMMAND bushido prepare --dump=${CMAKE_BINARY_DIR}/bushido_dump.log ${init_bushido})
include(${init_bushido})

if((BUSHIDO_REVISIONS STREQUAL "pinned") OR(CMAKE_BUILD_TYPE MATCHES "Release"))
  set(bushido_revs "revisions pinned")
endif()

bushido(
	minver 1.0.0-rc.8
	${bushido_revs}
	git github.com/boostorg/boost boost-1.79.0 build=boost-build
)

set(Boost_USE_STATIC_RUNTIME ON CACHE BOOL "")

add_subdirectory("tcp_server")
add_subdirectory("tcp_server_test")
