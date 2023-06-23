#include "Language.hh"

#include "sp/settings/GlobalSettings.hh"

namespace SP::Language {

static GlobalSettings::Language GetFallback() {
    switch (SCGetLanguage()) {
    case SC_LANG_JAPANESE:
        return GlobalSettings::Language::Japanese;
    case SC_LANG_ENGLISH:
        if (REGION == REGION_E) {
            return GlobalSettings::Language::EnglishNTSC;
        }
        return GlobalSettings::Language::EnglishPAL;
    case SC_LANG_SIMP_CHINESE:
    case SC_LANG_TRAD_CHINESE:
        return GlobalSettings::Language::EnglishPAL;
    case SC_LANG_GERMAN:
        return GlobalSettings::Language::German;
    case SC_LANG_FRENCH:
        if (REGION == REGION_E) {
            return GlobalSettings::Language::FrenchNTSC;
        }
        return GlobalSettings::Language::FrenchPAL;
    case SC_LANG_SPANISH:
        if (REGION == REGION_E) {
            return GlobalSettings::Language::SpanishNTSC;
        }
        return GlobalSettings::Language::SpanishPAL;
    case SC_LANG_ITALIAN:
        return GlobalSettings::Language::Italian;
    case SC_LANG_DUTCH:
        return GlobalSettings::Language::Dutch;
    case SC_LANG_KOREAN:
        return GlobalSettings::Language::Korean;
    default:
        assert(false);
    }
}

Font GetFont() {
    auto language = GlobalSettings::Get<GlobalSettings::Setting::Language>();
    switch (language) {
    case GlobalSettings::Language::Korean:
    case GlobalSettings::Language::Unspecified:
        return Font::Korean;
    default:
        return Font::Basic;
    }
}

const char *GetBaseCode() {
    switch (REGION) {
    case REGION_P:
        return "E";
    case REGION_E:
        return "U";
    case REGION_J:
        return "J";
    case REGION_K:
        return "K";
    default:
        assert(false);
    }
}

const char *GetCode() {
    auto language = GlobalSettings::Get<GlobalSettings::Setting::Language>();
    if (language == GlobalSettings::Language::Unspecified) {
        language = GetFallback();
    }
    switch (language) {
    case GlobalSettings::Language::German:
        return "G";
    case GlobalSettings::Language::EnglishNTSC:
        return "U";
    case GlobalSettings::Language::EnglishPAL:
        return "E";
    case GlobalSettings::Language::SpanishNTSC:
        return "M";
    case GlobalSettings::Language::SpanishPAL:
        return "S";
    case GlobalSettings::Language::FrenchNTSC:
        return "Q";
    case GlobalSettings::Language::FrenchPAL:
        return "F";
    case GlobalSettings::Language::Korean:
        return "K";
    case GlobalSettings::Language::Italian:
        return "I";
    case GlobalSettings::Language::Dutch:
        return "N";
    case GlobalSettings::Language::Japanese:
        return "J";
    case GlobalSettings::Language::Unspecified:
        assert(false);
    }
    assert(false);
}

} // namespace SP::Language
