#pragma once

#include "game/ui/Font.hh"

namespace UI {

class FontManager {
public:
    REPLACE void init();

private:
    void initFont(u32 index, const char *file);

    Font *m_fonts[6];
};
static_assert(sizeof(FontManager) == 0x18);

} // namespace UI
