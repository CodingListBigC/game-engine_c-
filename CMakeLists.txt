cmake_minimum_required(VERSION 3.10)

# Project metadata
project(MyGameEngine VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Find SDL2 dependency
# On Linux, this usually uses the system's FindSDL2.cmake or pkg-config
find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(Freetype REQUIRED)
find_package(PkgConfig REQUIRED)


pkg_check_modules(JSONCPP REQUIRED jsoncpp)

# Link the library
# 2. Collect all source files
# This avoids the "undefined reference" error by ensuring all .cpp files are compiled
file(GLOB_RECURSE SOURCES "src/*.cpp")

# 3. Define the executable
add_executable(game_engine ${SOURCES})

# 4. Include directories (where your headers live)
target_include_directories(game_engine PRIVATE 
    src
    ${SDL2_INCLUDE_DIRS}
	${FREETYPE_INCLUDE_DIRS}
	${JSONCPP_INCLUDE_DIRS}
)

# 5. Link libraries
target_link_libraries(game_engine PRIVATE 
    ${SDL2_LIBRARIES}
	${FREETYPE_LIBRARIES}
	${JSONCPP_LIBRARIES}
		GLEW::GLEW
		OpenGL::GL
		glm::glm
)

# Optional: Set the output directory to .build like your original setup
set_target_properties(game_engine PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
