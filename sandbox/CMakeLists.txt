add_executable(sandbox  
        src/main.c  
)  
  
target_include_directories(sandbox  
        PRIVATE  
        ${CMAKE_SOURCE_DIR}/engine/include  
)  
  
target_link_libraries(sandbox  
        PRIVATE  
        engine  
)
