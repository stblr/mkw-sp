#pragma once

#include "sp/settings/GlobalSettings.hh"

namespace SP::Language {

enum class PluralCondition {
    Never = 0,
    NotOne = 1,
    GreaterThanOne = 3,
};

enum class Font {
    Basic,
    Korean,
};

PluralCondition GetPluralCondition();
Font GetFont();
const wchar_t *GetName(GlobalSettings::Language language);
const char *GetBaseCode();
const char *GetCode();
GlobalSettings::Language GetDefault();

} // namespace SP::Language
