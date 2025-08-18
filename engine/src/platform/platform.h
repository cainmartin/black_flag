//
// Created by Cain Martin on 2025/08/08.
//

#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdbool.h>

typedef struct Platform Platform;
struct InputSystem;

typedef struct PlatformAPI
{
    Platform* (*create)(int width, int height, const char* title, int vsync);
    void (*destroy)(Platform* platform);
    void* (*get_gl_proc)(const char* name);
    void (*poll_events)(const Platform* platform, struct InputSystem* input_system, bool* out_should_quit);
    void (*swap_buffers)(Platform* platform);
    double (*time_now_seconds)(void);
    void (*get_drawable_size)(Platform* platform, int* width, int* height);
} PlatformAPI;

const PlatformAPI* platform_get_api(void);

#endif //PLATFORM_H
