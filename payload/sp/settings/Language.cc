#include "Language.hh"

namespace SP::Language {

PluralCondition GetPluralCondition() {
    auto language = GlobalSettings::Get<GlobalSettings::Setting::Language>();
    if (language == GlobalSettings::Language::Unspecified) {
        language = GetDefault();
    }
    switch (language) {
    case GlobalSettings::Language::Korean:
    case GlobalSettings::Language::Japanese:
        return PluralCondition::Never;
    case GlobalSettings::Language::FrenchNTSC:
    case GlobalSettings::Language::FrenchPAL:
        return PluralCondition::GreaterThanOne;
    default:
        return PluralCondition::NotOne;
    }
}

Font GetFont() {
    auto language = GlobalSettings::Get<GlobalSettings::Setting::Language>();
    if (language == GlobalSettings::Language::Unspecified) {
        language = GetDefault();
    }
    switch (language) {
    case GlobalSettings::Language::Korean:
        return Font::Korean;
    default:
        return Font::Basic;
    }
}

const wchar_t *GetName(GlobalSettings::Language language) {
    switch (language) {
    case GlobalSettings::Language::German:
        return L"Deutsch";
    case GlobalSettings::Language::EnglishNTSC:
        return L"English (NTSC)";
    case GlobalSettings::Language::EnglishPAL:
        return L"English (PAL)";
    case GlobalSettings::Language::SpanishNTSC:
        return L"Español (NTSC)";
    case GlobalSettings::Language::SpanishPAL:
        return L"Español (PAL)";
    case GlobalSettings::Language::FrenchNTSC:
        return L"Français (NTSC)";
    case GlobalSettings::Language::FrenchPAL:
        return L"Français (PAL)";
    case GlobalSettings::Language::Korean:
        return L"한국어";
    case GlobalSettings::Language::Italian:
        return L"Italiano";
    case GlobalSettings::Language::Dutch:
        return L"Nederlands";
    case GlobalSettings::Language::Japanese:
        return L"日本語";
    case GlobalSettings::Language::Unspecified:
        return L"Undefined";
    }
    assert(false);
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
        language = GetDefault();
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

GlobalSettings::Language GetDefault() {
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

} // namespace SP::Language
