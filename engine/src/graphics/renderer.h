//
// Created by Cain Martin on 2025/08/08.
//

#ifndef RENDERER_H
#define RENDERER_H

#include "../../include/engine.h"

typedef struct Renderer Renderer;

typedef struct RendererCreateInfo
{
    const struct PlatformAPI* platform_api; // Opaque bridge
    struct Platform* platform;
    int fb_width, fb_height;
} RendererCreateInfo;

typedef uint32_t R_Handle;

typedef struct RendererAPI {
    Renderer* (*create)(RendererCreateInfo *create_info);
    void (*destroy)(Renderer* renderer);
    void (*begin_frame)(Renderer* renderer, int fb_w, int fb_h);
    void (*end_frame)(Renderer* renderer);
    void (*clear)(Renderer* renderer, float red, float green, float blue, float alpha);
    void (*present)(Renderer* renderer);

    // Resources
    R_Handle (*mesh_create)(Renderer*, const EngineMeshDesc*);
    void (*mesh_destroy)(Renderer* mesh, R_Handle);

    R_Handle (*shader_create)(Renderer*, const char* vs_src, const char* fs_src);
    void (*shader_destroy)(Renderer*, R_Handle);

    R_Handle (*texture_create)(Renderer*, const EngineTextureDesc*);
    void (*texture_destroy)(Renderer*, R_Handle);

    R_Handle (*material_create)(Renderer*, const EngineMaterialDesc*);
    void (*material_destroy)(Renderer*, R_Handle);

    // State
    void (*set_camera)(Renderer*, const EngineCamera*);

    // Uniforms by name
    void (*material_set_uniform_f)(Renderer*, R_Handle mat, const char* name, const float* val, int count);
} RendererAPI;

const RendererAPI* get_renderer_api(void);

#endif //RENDERER_H
