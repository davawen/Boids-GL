cmake_minimum_required(VERSION 3.12...3.21)

# Flags / Options
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG_ON")

set(PROJECT_NAME "learn-opengl")

project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)

# Add source files
file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/src/*.c
	${CMAKE_SOURCE_DIR}/src/*.cpp)

# Add header files
file(GLOB_RECURSE HEADER_FILES 
	${CMAKE_SOURCE_DIR}/include/*.h
	${CMAKE_SOURCE_DIR}/include/*.hpp)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

# Headers
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Libraries
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} Threads::Threads)

find_package(OpenGL REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${OpenGL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} GL)

find_package(glfw3 REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${glfw_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} glfw)

find_package(GLEW REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${GLEW_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})

find_package(fmt REQUIRED)
target_link_libraries(${PROJECT_NAME} fmt::fmt)

# Link assets
if(NOT COPY_ASSETS)
	set(COPY_ASSETS OFF)
endif()

add_custom_target(copy_assets ALL
	DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/assets/
)

if(COPY_ASSETS)
	add_custom_command(
		OUTPUT
			${CMAKE_CURRENT_BINARY_DIR}/assets/
		COMMAND
			cp -r
			${CMAKE_SOURCE_DIR}/assets/
			${CMAKE_CURRENT_BINARY_DIR}/assets/
	)
else()
	add_custom_command(
		OUTPUT
			${CMAKE_CURRENT_BINARY_DIR}/assets/
		COMMAND
			ln -sf
			${CMAKE_SOURCE_DIR}/assets
			${CMAKE_CURRENT_BINARY_DIR}/assets
	)
endif()

add_dependencies(${PROJECT_NAME} copy_assets)

# Compilation

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	target_compile_options(${PROJECT_NAME} PRIVATE /W4)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Wno-unknown-pragmas)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
	target_compile_options(${PROJECT_NAME} PRIVATE)
endif()
