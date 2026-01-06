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

target_compile_options(project_options
    INTERFACE
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

target_compile_definitions(project_options
    INTERFACE
        $<$<CONFIG:Debug>:ANGINA_DEBUG>
)
