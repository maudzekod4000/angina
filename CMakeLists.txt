cmake_minimum_required(VERSION 3.28.0)

set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

include(${DIR}/cmake_helpers/helpers.cmake)
set(CMAKE_MODULE_PATH
	${CMAKE_MODULE_PATH}
	${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers/find_modules)

project(angina LANGUAGES CXX)

include(${DIR}/cmake_helpers/ProjectOptions.cmake)

add_subdirectory(platform)
add_subdirectory(backend)
add_subdirectory(ui)
add_subdirectory(core)

file(GLOB_RECURSE ENGINE_SOURCES
	${DIR}/enginev3/*.cpp
	${DIR}/enginev3/*.h
)

file(GLOB_RECURSE RENDERER_SOURCES
	${DIR}/renderer/*.cpp
	${DIR}/renderer/*.h
)

file(GLOB_RECURSE CHESS_SOURCES
	${DIR}/examples/chess/*.cpp
	${DIR}/examples/chess/*.h
)

add_executable(${PROJECT_NAME}
	${DIR}/main.cpp
	${ENGINE_SOURCES}
	${DIR}/exceptions/BaseException.cpp
)

set_target_cpp_standard(${PROJECT_NAME} 23)

if (MSVC)
    target_compile_options(${PROJECT_NAME}
        PRIVATE
            /W4
            /permissive-
            /Zc:__cplusplus
            /Zc:preprocessor
            /EHsc
            /diagnostics:caret

            # Extra warnings
            /w14242
            /w14254
            /w14263
            /w14265
            /w14287
            /w14296

            # Disable noisy warnings
            /wd4100
            /wd4201
            /wd4324
            /wd4251
            /wd4275

            # Warnings as errors (Debug only)
            $<$<CONFIG:Debug>:/WX>
    )
endif()
if (UNIX)
    enable_target_warnings(${PROJECT_NAME})
endif (UNIX)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        $<$<CONFIG:Debug>:ANGINA_DEBUG>
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_CURRENT_SOURCE_DIR}/resources
	$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)

target_include_directories(${PROJECT_NAME} PRIVATE ${DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE 
	platform
	backend
    ui
    core
)
