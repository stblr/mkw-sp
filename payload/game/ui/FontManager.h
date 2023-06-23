#pragma once

#include "Font.h"

typedef struct {
    Font *fonts[6];
} FontManager;
static_assert(sizeof(FontManager) == 0x18);

extern FontManager *s_fontManager;
