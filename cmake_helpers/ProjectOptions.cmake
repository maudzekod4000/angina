add_library(project_options INTERFACE)

target_compile_features(project_options
    INTERFACE
        cxx_std_23
)

set_target_properties(project_options PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

if (MSVC)
    target_compile_options(project_options
        INTERFACE
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

target_compile_definitions(project_options
    INTERFACE
        $<$<CONFIG:Debug>:ANGINA_DEBUG>
)
