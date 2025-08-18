//
// Created by Cain Martin on 2025/08/08.
//

#ifndef ENGINE_INTERNAL_H
#define ENGINE_INTERNAL_H

#include <stdbool.h>

typedef struct InputSystem InputSystem;
InputSystem* input_create(void);
void input_destroy(InputSystem* input);
void input_begin_frame(InputSystem* input);
void input_set_key(InputSystem* input, EngineKey engine_key, bool down);
bool input_is_down(const InputSystem* input, EngineKey engine_key);
bool input_was_pressed(const InputSystem* input, EngineKey engine_key);
bool input_was_released(const InputSystem* input, EngineKey engine_key);

#endif //ENGINE_INTERNAL_H
