#ifndef ENGINE_H
#define ENGINE_H

#include <stdbool.h>

typedef struct Engine Engine;

typedef void (*update_callback)(Engine* engine, float delta_time);

typedef struct Engine {
    void* window;
    void* context;
    bool should_quit;
} Engine;

typedef struct EngineConfig {
    int width;
    int height;
    const char* title;
    update_callback update_callback;
    void* user_data;
} EngineConfig;

Engine* engine_create(const EngineConfig* config);
void engine_run(Engine* engine);
bool engine_should_quit(Engine* engine);
void engine_shutdown(Engine* engine);

#endif // ENGINE_H