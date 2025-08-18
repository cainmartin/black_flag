//
// Created by Cain Martin on 2025/08/08.
//

#include <stdlib.h>
#include "../../include/engine.h"
#include "engine_internal.h"
#include "../platform/platform.h"
#include "../graphics/renderer.h"

struct InputSystem; // Forward from input.c

struct Engine {
    Platform*              platform;
    const PlatformAPI*     plat_api;
    Renderer*              renderer;
    const RendererAPI*     rend_api;
    InputSystem*           input;
    float                  delta_time;
    double                 last_time;
    double                 elapsed;
    bool                   should_quit;
    void*                  user_data;
};

Engine* engine_create(const EngineConfig* cfg) {
    Engine* engine = calloc(1, sizeof *engine);
    if (!engine) return NULL;

    engine->plat_api = platform_get_api();
    engine->platform = engine->plat_api->create(cfg->width, cfg->height, cfg->title, cfg->vsync ? 1 : 0);
    if (!engine->platform)
    {
        engine->plat_api->destroy(engine->platform);
        free(engine);
        return NULL;
    }

    engine->rend_api = get_renderer_api();

    RendererCreateInfo renderer_create_info =
    {
        .platform_api = engine->plat_api,
        .platform = engine->platform,
        .fb_width = cfg->width,
        .fb_height = cfg->height
    };

    engine->renderer = engine->rend_api->create(&renderer_create_info);
    if (!engine->renderer)
    {
        engine->plat_api->destroy(engine->platform);
        free(engine);
        return NULL;
    }

    engine->input    = input_create();
    engine->user_data = cfg->user_data;

    engine->last_time = engine->plat_api->time_now_seconds();
    engine->elapsed   = 0.0;

    return engine;
}

void engine_shutdown(Engine* e) {
    if (!e) return;
    input_destroy(e->input);
    e->rend_api->destroy(e->renderer);
    e->plat_api->destroy(e->platform);
    free(e);
}

void engine_begin_frame(Engine* e) {
    input_begin_frame(e->input);

    bool quit = false;
    e->plat_api->poll_events(e->platform, e->input, &quit);
    if (quit) e->should_quit = true;

    double now = e->plat_api->time_now_seconds();
    e->delta_time = (float)(now - e->last_time);
    e->elapsed += (now - e->last_time);
    e->last_time = now;

    int w = 0;
    int h = 0;
    e->plat_api->get_drawable_size(e->platform, &w, &h);
    e->rend_api->begin_frame(e->renderer, w, h);
}

void engine_end_frame(Engine* e) {
    e->rend_api->end_frame(e->renderer);
    e->rend_api->present(e->renderer);
}

void engine_clear(Engine* e, float r, float g, float b, float a) {
    e->rend_api->clear(e->renderer, r, g, b, a);
}

bool engine_should_quit(const Engine* e) { return e->should_quit; }
float engine_get_delta_time(const Engine* e) { return e->delta_time; }
double engine_get_elapsed_time(const Engine* e) { return e->elapsed; }
bool engine_is_key_down(const Engine* e, EngineKey k) { return input_is_down(e->input, k); }
bool engine_was_key_pressed(const Engine* e, EngineKey k) { return input_was_pressed(e->input, k); }
bool engine_was_key_released(const Engine* e, EngineKey k) { return input_was_released(e->input, k); }
void* engine_get_user_data(const Engine* e) { return e->user_data; }


// Create methods
MeshHandle engine_mesh_create(Engine* engine, const EngineMeshDesc* desc)
{
    if (!engine || !desc) return 0;
    return (MeshHandle)engine->rend_api->mesh_create(engine->renderer, desc);
}

void engine_mesh_destroy(Engine* engine, MeshHandle handle)
{
    if (!engine || !handle) return;
    return engine->rend_api->mesh_destroy(engine->renderer, handle);
}

ShaderHandle engine_shader_create(Engine* engine, const char* vs_source, const char* fs_source)
{
    if (!engine || !vs_source || !fs_source) return 0;
    return engine->rend_api->shader_create(engine->renderer, vs_source, fs_source);
}

void engine_shader_destroy(Engine* engine, ShaderHandle handle)
{
    if (!engine || !handle) return;
    return engine->rend_api->shader_destroy(engine->renderer, handle);
}

TextureHandle engine_texture_create(Engine* engine, const EngineTextureDesc* desc)
{
    if (!engine || !desc) return 0;
    return (TextureHandle)engine->rend_api->texture_create(engine->renderer, desc);
}

void engine_texture_destroy(Engine* engine, TextureHandle handle)
{
    if (!engine || !handle) return;
    return engine->rend_api->texture_destroy(engine->renderer, handle);
}

MaterialHandle engine_material_create(Engine* engine, const EngineMaterialDesc* desc)
{
    if (!engine || !desc) return 0;
    return (MaterialHandle)engine->rend_api->material_create(engine->renderer, desc);
}

void engine_material_destroy(Engine* engine, MaterialHandle handle)
{
    if (!engine || !handle) return;
    return engine->rend_api->material_destroy(engine->renderer, handle);
}