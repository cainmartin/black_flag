#ifndef ENGINE_H
#define ENGINE_H

#include <stdbool.h>
#include <stdint.h>

typedef struct Engine Engine;

typedef struct EngineConfig {
    int width;
    int height;
    const char* title;
    int vsync;
    void* user_data; // Placeholder for now - add additional user_data for subsystems
} EngineConfig;

typedef enum {
    KEY_A = 0,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,
    KEY_0,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_SPACE,
    KEY_ESCAPE,
    KEY_ENTER,

    KEY_COUNT,
} EngineKey;

//
typedef uint32_t MeshHandle;
typedef uint32_t ShaderHandle;
typedef uint32_t TextureHandle;
typedef uint32_t MaterialHandle;

// Vertex format used by the default pipeline
typedef struct {
    float pos[3];
    float normal[3];
    float uv[2];
} EngineVertex;

typedef struct {
    const EngineVertex* vertices;
    uint32_t vertex_count;
    const uint32_t* indices;
    uint32_t indices_count;
} EngineMeshDesc;

typedef enum {
    ENGINE_TEXTURE_RGBA8,
    ENGINE_TEXTURE_RGB8,
    ENGINE_TEXTURE_R8,
    // TO ADD LATER - ENGINE_TEXTURE_SRGB8_A8
} EngineTextureFormat;

typedef struct {
    int width, height;
    EngineTextureFormat format;
    const void* pixels; // Tightly packed for now - add pitch later if required...
} EngineTextureDesc;

 // Basic material: 1 + shader and up to 4 textures
typedef struct {
    ShaderHandle shader;
    TextureHandle texture[4];
    int texture_count;
    int depth_test;
    int depth_write;
    int blend;
} EngineMaterialDesc;

typedef struct {
    float view[16];
    float projection[16];
    float inverse_projection[16];
    float view_position[3];
} EngineCamera;

// Create methods
MeshHandle engine_mesh_create(Engine*, const EngineMeshDesc*);
void    engine_mesh_destroy(Engine*, MeshHandle);

ShaderHandle engine_shader_create(Engine*, const char* vs_source, const char* fs_source);
void    engine_shader_destroy(Engine*, ShaderHandle);

TextureHandle engine_texture_create(Engine*, const EngineTextureDesc*);
void    engine_texture_destroy(Engine*, TextureHandle);

MaterialHandle engine_material_create(Engine*, const EngineMaterialDesc*);
void    engine_material_destroy(Engine*, MaterialHandle);

// Per Frame
void    engine_set_camera(Engine*, const EngineCamera*);
void    engine_draw(Engine*, MeshHandle, MaterialHandle, const float model[16]);

// Optionally set per-material uniforms (common case: a few floats)
void    engine_set_uniform_f(Engine*, MaterialHandle, const char* name, const float* vals, int count);

Engine* engine_create(const EngineConfig* cfg);
void    engine_shutdown(Engine* e);

void    engine_begin_frame(Engine* e);   // polls input/events, computes dt
void    engine_end_frame(Engine* e);     // presents

void    engine_clear(Engine* e, float r, float g, float b, float a);

bool    engine_should_quit(const Engine* e);

float   engine_get_delta_time(const Engine* e);
double  engine_get_elapsed_time(const Engine* e);

bool    engine_is_key_down(const Engine* e, EngineKey key);
bool    engine_was_key_pressed(const Engine* e, EngineKey key);  // pressed this frame
bool    engine_was_key_released(const Engine* e, EngineKey key); // released this frame

void*   engine_get_user_data(const Engine* e); // optional convenience

#endif // ENGINE_H