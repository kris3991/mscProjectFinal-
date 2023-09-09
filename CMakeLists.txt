cmake_minimum_required(VERSION 3.12)
project(MScProject)

# Find CUDA
find_package(CUDA REQUIRED)

# Add the CUDA_NVCC_FLAGS for setting GPU architecture (optional)
set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS};-arch=sm_35)

add_compile_definitions(_CRT_SECURE_NO_WARNINGS)

#common vars
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

set (CMAKE_CXX_STANDARD 17)

#setup Imgui
set(IMGUIDIR "external/imgui")
include_directories(${IMGUIDIR} ${IMGUIDIR}/backends)
aux_source_directory("${IMGUIDIR}/" IMGUICORE)
set(IMGUIBACKENDS "${IMGUIDIR}/backends/imgui_impl_opengl3.cpp" 
  "${IMGUIDIR}/backends/imgui_impl_glfw.cpp"
  "${IMGUIDIR}/misc/cpp/imgui_stdlib.cpp"
)

set(SOURCES 
src/main.cpp
#external library headers begin
${IMGUICORE} 
${IMGUIBACKENDS}
#tiny file loader for dialogs.
external/tinyfiledialogs/tinyfiledialogs.c
#external lib files end

#test file to verify build
src/vector_addition.cu
#triangle
src/triangle.cpp
#initialise
src/initialise.cpp
#file manager
src/fileManager.cpp
)

file(GLOB HEADER_FILES ${CMAKE_SOURCE_DIR}/include/*.h ${CMAKE_SOURCE_DIR}/include/*.cuh)

# Create an executable target
cuda_add_executable(${PROJECT_NAME} ${SOURCES} ${HEADER_FILES})

#add glfw
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(USE_MSVC_RUNTIME_LIBRARY_DLL OFF CACHE BOOL "" FORCE)
add_subdirectory("external/glfw-3.3.6")

#add glew
set(BUILD_UTILS OFF CACHE BOOL "" FORCE)
add_subdirectory("external/glew-2.1.0/build/cmake")

#add glm
add_subdirectory("external/glm")


# Link CUDA libraries
target_link_libraries(${PROJECT_NAME} ${CUDA_LIBRARIES} glfw opengl32 glew_s glm)

# Include the 'include' directory as a target include directory
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/external/glew-2.1.0/include)

# Create a custom target to display each header file individually in IDE
foreach(HEADER ${HEADER_FILES})
    get_filename_component(HEADER_NAME ${HEADER} NAME)
    source_group("Header Files" FILES ${HEADER})
endforeach()

