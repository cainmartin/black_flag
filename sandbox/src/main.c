#include <stdio.h>
#include "engine.h"

int main(void) {
    const EngineConfig cfg = { .width = 1280, .height = 720, .title = "Donkey Fartbox", .vsync = 1 };
    Engine* eng = engine_create(&cfg);
    if (!eng) return 1;

    while (!engine_should_quit(eng)) {
        engine_begin_frame(eng);

        if (engine_was_key_pressed(eng, KEY_ESCAPE)) break;

        engine_clear(eng, 1.0f, 0.12f, 0.15f, 1.0f);

        engine_end_frame(eng);
    }

    engine_shutdown(eng);
    return 0;
}