//
// Created by Cain Martin on 2025/08/13.
//

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../../include/engine.h"

typedef struct InputSystem
{
    bool down[KEY_COUNT];
    bool pressed[KEY_COUNT];
    bool released[KEY_COUNT];
} InputSystem;

InputSystem* input_create(void)
{
    return calloc(1, sizeof(InputSystem));
}

void input_destroy(InputSystem* input)
{
    free(input);
}

void input_begin_frame(InputSystem* input)
{
    memset(input->pressed, 0, sizeof input->pressed);
    memset(input->released, 0, sizeof input->released);
}

void input_set_key(InputSystem* input, EngineKey key, bool down)
{
    if (key >= KEY_COUNT) return;
    if (down && !input->down[key]) input->pressed[key] = true;
    if (!down && input->down[key]) input->released[key] = true;
    input->down[key] = down;
}

bool input_is_down(const InputSystem* input, EngineKey key) { return key < KEY_COUNT && input->down[key]; }
bool input_was_pressed(const InputSystem* input, EngineKey key) { return key < KEY_COUNT && input->pressed[key]; }
bool input_was_released(const InputSystem* input, EngineKey key) { return key < KEY_COUNT && input->released[key]; }