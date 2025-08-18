add_library(engine STATIC
        src/core/file_io.c
        src/core/file_io.h
        src/platform/sdl_platform.c
        src/platform/platform.h
        src/graphics/backends/opengl_renderer.c
        src/graphics/renderer.h
        src/core/engine_internal.h
        src/core/engine.c
        src/core/input.c
        src/core/d_array.c
        src/core/d_array.h
)
  
target_include_directories(engine  
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)  
  
target_compile_features(engine PUBLIC c_std_99)  
  
target_link_libraries(engine  
        PUBLIC  
        SDL3::SDL3
        glad  
        OpenGL::GL  
        cglm
)
