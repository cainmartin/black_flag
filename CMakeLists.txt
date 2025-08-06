cmake_minimum_required(VERSION 3.21)  
  
project(black_flag C)
  
set(CMAKE_C_STANDARD 99)
  
include(FetchContent)  
  
FetchContent_Declare(  
        glad  
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git  
        GIT_TAG v0.1.36  
)  
  
# Configure GLAD options before making it available  
set(GLAD_PROFILE "core" CACHE STRING "OpenGL profile")  
set(GLAD_API "gl=3.3" CACHE STRING "API type/version pairs, like \"gl=3.3,gles=\", no version means latest")  
set(GLAD_GENERATOR "c" CACHE STRING "Language to generate the binding for")  
FetchContent_MakeAvailable(glad)  
  
FetchContent_Declare(  
        sdl3  
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git  
        GIT_TAG release-3.2.20
)  
FetchContent_MakeAvailable(sdl3)  

FetchContent_Declare(  
        cglm  
        GIT_REPOSITORY https://github.com/recp/cglm.git  
        GIT_TAG v0.9.6  
)
FetchContent_MakeAvailable(cglm)  
  
find_package(OpenGL REQUIRED)  
  
add_subdirectory(engine)  
add_subdirectory(sandbox)
