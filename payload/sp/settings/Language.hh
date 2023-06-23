#pragma once

#include "sp/settings/GlobalSettings.hh"

namespace SP::Language {

enum class Font {
    Basic,
    Korean,
};

Font GetFont();
const wchar_t *GetName(GlobalSettings::Language language);
const char *GetBaseCode();
const char *GetCode();
GlobalSettings::Language GetDefault();

} // namespace SP::Language
