//
// Created by Cain Martin on 2025/08/07.
//

#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>
#include <stdlib.h>
#include "platform.h"
#include "../../include/engine.h" // For EngineKey mapping

struct Platform
{
    SDL_Window* window;
    SDL_GLContext gl;
};

static Platform* sdl_create(int w, int h, const char* title, int vsync)
{
    if (SDL_Init(SDL_INIT_VIDEO) == false) return NULL;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    if (__APPLE__)
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

    SDL_Window* window = SDL_CreateWindow(title, w, h, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!window) return NULL;

    SDL_GLContext context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, context);
    SDL_GL_SetSwapInterval(vsync ? 1 : 0);

    Platform* p = malloc(sizeof(*p));
    if (!p) return NULL;

    p->window = window;
    p->gl = context;

    return p;
}

static void sdl_destroy(Platform* platform)
{
    if (!platform) return;

    SDL_GL_DestroyContext(platform->gl);
    SDL_DestroyWindow(platform->window);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);

    free(platform);
}

static void* sdl_get_gl_proc(const char* name)
{
    return SDL_GL_GetProcAddress(name);
}

static void sdl_swap_buffers(Platform* platform)
{
    SDL_GL_SwapWindow(platform->window);
}

static EngineKey map_scancode(SDL_Scancode scancode)
{
    switch (scancode) {
        case SDL_SCANCODE_A: return KEY_A;
        case SDL_SCANCODE_B: return KEY_B;
        case SDL_SCANCODE_C: return KEY_C;
        case SDL_SCANCODE_D: return KEY_D;
        case SDL_SCANCODE_E: return KEY_E;
        case SDL_SCANCODE_F: return KEY_F;
        case SDL_SCANCODE_G: return KEY_G;
        case SDL_SCANCODE_H: return KEY_H;
        case SDL_SCANCODE_I: return KEY_I;
        case SDL_SCANCODE_J: return KEY_J;
        case SDL_SCANCODE_K: return KEY_K;
        case SDL_SCANCODE_L: return KEY_L;
        case SDL_SCANCODE_M: return KEY_M;
        case SDL_SCANCODE_N: return KEY_N;
        case SDL_SCANCODE_O: return KEY_O;
        case SDL_SCANCODE_P: return KEY_P;
        case SDL_SCANCODE_Q: return KEY_Q;
        case SDL_SCANCODE_R: return KEY_R;
        case SDL_SCANCODE_S: return KEY_S;
        case SDL_SCANCODE_T: return KEY_T;
        case SDL_SCANCODE_U: return KEY_U;
        case SDL_SCANCODE_V: return KEY_V;
        case SDL_SCANCODE_W: return KEY_W;
        case SDL_SCANCODE_X: return KEY_X;
        case SDL_SCANCODE_Y: return KEY_Y;
        case SDL_SCANCODE_Z: return KEY_Z;
        case SDL_SCANCODE_0: return KEY_0;
        case SDL_SCANCODE_1: return KEY_1;
        case SDL_SCANCODE_2: return KEY_2;
        case SDL_SCANCODE_3: return KEY_3;
        case SDL_SCANCODE_4: return KEY_4;
        case SDL_SCANCODE_5: return KEY_5;
        case SDL_SCANCODE_6: return KEY_6;
        case SDL_SCANCODE_7: return KEY_7;
        case SDL_SCANCODE_8: return KEY_8;
        case SDL_SCANCODE_9: return KEY_9;
        case SDL_SCANCODE_SPACE:   return KEY_SPACE;
        case SDL_SCANCODE_ESCAPE:  return KEY_ESCAPE;
        case SDL_SCANCODE_RETURN:  return KEY_ENTER;
        default: return KEY_COUNT;
    }
}

extern void input_set_key(struct InputSystem* input_system, EngineKey key, bool pressed); // From input.c

static void sdl_poll_events(const Platform* platform, struct InputSystem* input_system, bool* out_should_quit)
{
    (void)platform;

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_EVENT_QUIT:
                *out_should_quit = true;
                break;
            case SDL_EVENT_KEY_DOWN: {
                EngineKey key = map_scancode(event.key.scancode);
                if (key != KEY_COUNT) input_set_key(input_system, key, true);
            }
        }
    }
}

static double sdl_time_now_seconds(void)
{
    static double freq_inv = 0.0;
    if (freq_inv == 0.0) freq_inv = 1.0 / (double) SDL_GetPerformanceFrequency();

    return (double)SDL_GetPerformanceCounter() * freq_inv;
}

static void sdl_get_drawable_size(Platform* p, int* w, int* h) {
    SDL_GetWindowSizeInPixels(p->window, w, h);
}

const PlatformAPI* platform_get_api(void)
{
    static const PlatformAPI api = {
        .create = sdl_create,
        .destroy = sdl_destroy,
        .get_gl_proc = sdl_get_gl_proc,
        .swap_buffers = sdl_swap_buffers,
        .poll_events = sdl_poll_events,
        .time_now_seconds = sdl_time_now_seconds,
        .get_drawable_size = sdl_get_drawable_size,
    };

    return &api;
}



