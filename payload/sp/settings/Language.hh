#pragma once

namespace SP::Language {

enum class Font {
    Basic,
    Korean,
};

Font GetFont();
const char *GetBaseCode();
const char *GetCode();

} // namespace SP::Language
