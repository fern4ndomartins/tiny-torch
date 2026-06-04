cmake_minimum_required(VERSION 3.10)
project(modd)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find dependencies
find_package(glfw3 REQUIRED)
find_package(Vulkan REQUIRED)
find_package(Python COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 CONFIG REQUIRED)

# Find glslc (Vulkan shader compiler)
find_program(GLSLC_EXECUTABLE glslc HINTS "$ENV{VULKAN_SDK}/bin")
if(NOT GLSLC_EXECUTABLE)
    message(FATAL_ERROR "glslc not found - set VULKAN_SDK or install glslc")
endif()

# Collect all shader source files
file(GLOB_RECURSE GLSL_SHADERS
    "${CMAKE_SOURCE_DIR}/shaders/*.vert"
    "${CMAKE_SOURCE_DIR}/shaders/*.frag"
    "${CMAKE_SOURCE_DIR}/shaders/*.comp"
)

set(SPIRV_OUTPUT_DIR "${CMAKE_BINARY_DIR}/shaders")
set(SPIRV_BINARY_FILES "")

foreach(GLSL ${GLSL_SHADERS})
    get_filename_component(FILE_BASENAME ${GLSL} NAME_WE)   # filename without extension
    get_filename_component(FILE_EXT ${GLSL} EXT)            # extension including dot, e.g. .vert
    # Remove the leading dot to use as suffix
    string(SUBSTRING ${FILE_EXT} 1 -1 EXT_SUFFIX)
    set(SPIRV "${SPIRV_OUTPUT_DIR}/${FILE_BASENAME}_${EXT_SUFFIX}.spv")

    add_custom_command(
        OUTPUT ${SPIRV}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${SPIRV_OUTPUT_DIR}
        COMMAND ${GLSLC_EXECUTABLE} ${GLSL} -o ${SPIRV}
        DEPENDS ${GLSL}
        COMMENT "Compiling shader: ${FILE_BASENAME}${FILE_EXT}"
        VERBATIM
    )
    list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach()

# Custom target that triggers shader compilation
add_custom_target(Shaders ALL DEPENDS ${SPIRV_BINARY_FILES})

# Create the Python module
pybind11_add_module(modd MODULE src/modd.cc
    src/cmb.cc
    src/device.cc
    src/pipeline.cc
    src/common.cc
    src/instance.cc
    src/mem.cc
    src/wsi.cc)

# Make sure shaders are built before the module (so they exist at runtime)
add_dependencies(modd Shaders)

# Link Vulkan and GLFW
target_link_libraries(modd PRIVATE Vulkan::Vulkan glfw)

# On some platforms you may need these (uncomment if missing):
# target_link_libraries(modd PRIVATE ${CMAKE_DL_LIBS})  # for dlopen
# if(UNIX AND NOT APPLE)
#     target_link_libraries(modd PRIVATE pthread)
# endif()

# Remove the default 'lib' prefix on Unix (so module is modd.so, not libmodd.so)
set_target_properties(modd PROPERTIES PREFIX "")