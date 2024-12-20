#pragma once

#include <stddef.h>

const char *to_bool_string(int b);
char **split(char *str, size_t *size);
void fps_draw();
void score_draw(int score);
