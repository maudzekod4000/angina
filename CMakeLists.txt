cmake_minimum_required(VERSION 3.28.0)

set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

include(${DIR}/cmake_helpers/helpers.cmake)
set(CMAKE_MODULE_PATH
${CMAKE_MODULE_PATH}
${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/find_modules)

project(angina LANGUAGES CXX)

add_subdirectory(platform)

file(GLOB_RECURSE ENGINE_SOURCES
	${DIR}/enginev3/*.cpp
	${DIR}/enginev3/*.h
)

file(GLOB_RECURSE RENDERER_SOURCES
	${DIR}/renderer/*.cpp
	${DIR}/renderer/*.h
)

file(GLOB_RECURSE CORE_SOURCES
	#${DIR}/core/*.cpp
	#${DIR}/core/*.h
	${DIR}/core/units/Units.ixx
)

file(GLOB_RECURSE UI_SOURCES
	${DIR}/ui/*.cpp
	${DIR}/ui/*.h
)

file(GLOB_RECURSE CHESS_SOURCES
	${DIR}/examples/chess/*.cpp
	${DIR}/examples/chess/*.h
)

add_executable(${PROJECT_NAME}
	${DIR}/main.cpp
	${ENGINE_SOURCES}
	${CORE_SOURCES}
	${UI_SOURCES}
	${DIR}/exceptions/BaseException.cpp
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_CURRENT_SOURCE_DIR}/resources
	$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)

set_target_cpp_standard(${PROJECT_NAME} 23)

if (UNIX)
enable_target_warnings(${PROJECT_NAME})
endif (UNIX)


find_package(SDL2 REQUIRED)

if (WIN32)
	find_package(SDL2_IMAGE REQUIRED)
endif (WIN32)

if (UNIX)
	find_package(SDL2_image REQUIRED)
endif (UNIX)

if (UNIX)
	find_package(SDL2_ttf REQUIRED)
endif (UNIX)

if (WIN32)
	find_package(SDL2_TTF REQUIRED)
endif (WIN32)

if (WIN32)
	find_package(SDL2_MIXER REQUIRED)
endif (WIN32)

if (UNIX)
	find_package(SDL2_mixer REQUIRED)
endif (UNIX)

target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${INTERFACE_INCLUDE_DIRECTORIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE 
	${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} ${SDL2_MIXER_LIBRARY}
	platform
)
