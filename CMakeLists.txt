cmake_minimum_required(VERSION 4.0.0)

project(genpasswd LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2")

set(SOURCE genpasswd.cpp)

set(LOCAL_BIN "$ENV{HOME}/.local/bin")
set(LOCAL_MAN "$ENV{HOME}/.local/share/man/man1")

add_executable(${PROJECT_NAME} ${SOURCE})

install(TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION ${LOCAL_BIN})

install(FILES genpasswd.1
	DESTINATION ${LOCAL_MAN})

