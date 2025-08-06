add_library(engine STATIC  
        src/engine.c  
)  
  
target_include_directories(engine  
        PUBLIC  
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
)  
  
target_compile_features(engine PUBLIC c_std_99)  
  
target_link_libraries(engine  
        PUBLIC  
        SDL3::SDL3
        glad  
        OpenGL::GL  
        cglm
)
