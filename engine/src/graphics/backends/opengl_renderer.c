//
// Created by Cain Martin on 2025/08/08.
//

#include <glad/glad.h>
#include <stdlib.h>
#include <sys/proc.h>
#include "../../platform/platform.h"
#include "../renderer.h"

typedef struct GLRenderer
{
    const PlatformAPI* plat;
    Platform*          platform;
    int                w,h;
} GLRenderer;

static Renderer* gl_create(RendererCreateInfo* create_info)
{
    GLRenderer* renderer = malloc(sizeof(*renderer));
    if (!renderer) { return NULL;}

    renderer->plat = create_info->platform_api;
    renderer->platform = create_info->platform;
    renderer->w = create_info->fb_width;
    renderer->h = create_info->fb_height;

    // Load GL after context is current
    if (gladLoadGLLoader((GLADloadproc)renderer->plat->get_gl_proc) == 0) {
        free(renderer);
        return NULL;
    }

    return (Renderer*)renderer;
}

static void gl_destroy(Renderer* renderer)
{
    free(renderer);
}

static void gl_begin(Renderer* renderer, int fb_w, int fb_h)
{
    (void)renderer;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, fb_w, fb_h);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    // Do not clear here - allow user to call engine_clear
}

static void gl_end(Renderer* renderer)
{
    (void)renderer;
    // Swap happens in the platform layer
}

static void present(Renderer* renderer)
{
    GLRenderer* r = (GLRenderer*)renderer;
    r->plat->swap_buffers(r->platform);
}

static void gl_clear(Renderer* renderer, float red, float green, float blue, float alpha)
{
    (void)renderer;
    glClearColor(red, green, blue, alpha);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// Resources

R_Handle mesh_create(Renderer* renderer, const EngineMeshDesc* desc)
{
    return 0;
}

void mesh_destroy(Renderer* renderer, R_Handle handle)
{
}

R_Handle shader_create(Renderer* renderer, const char* vs_src, const char* fs_src)
{
    return 0;
}

void shader_destroy(Renderer* renderer, R_Handle handle)
{
}

R_Handle texture_create(Renderer* renderer, const EngineTextureDesc* desc)
{
    return 0;
}

void texture_destroy(Renderer* renderer, R_Handle handle)
{

}

R_Handle material_create(Renderer* renderer, const EngineMaterialDesc* desc)
{
    return 0;
}

void material_destroy(Renderer* renderer, R_Handle handle)
{

}

// State
void set_camera(Renderer* renderer, const EngineCamera* camera)
{

}

// Uniforms by name
void material_set_uniform_f(Renderer* renderer, R_Handle mat, const char* name, const float* val, int count)
{

}


static const RendererAPI api = {
    .create = gl_create,
    .destroy = gl_destroy,
    .begin_frame = gl_begin,
    .end_frame = gl_end,
    .clear = gl_clear,
    .present = present,
    // Resources
    .mesh_create = mesh_create,
    .mesh_destroy = mesh_destroy,
    .shader_create = shader_create,
    .shader_destroy = shader_destroy,
    .texture_create = texture_create,
    .texture_destroy = texture_destroy,
    .material_create = material_create,
    .material_destroy = material_destroy,
    .set_camera = set_camera,
    .material_set_uniform_f = material_set_uniform_f,
};

const RendererAPI* get_renderer_api(void) { return &api; }