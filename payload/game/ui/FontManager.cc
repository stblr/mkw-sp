#include "FontManager.hh"

namespace UI {

void FontManager::init() {
    switch (SCGetLanguage()) {
    case SC_LANG_KOREAN:
        if (REGION == REGION_K) {
            initFont(0, "tt_kart_font_rodan_ntlg_pro_b.brfnt");
        } else {
            initFont(0, "tt_kart_font_rodan_ntlg_pro_b_K.brfnt");
        }
        break;
    default:
        if (REGION == REGION_K) {
            initFont(0, "tt_kart_font_rodan_ntlg_pro_b_R.brfnt");
        } else {
            initFont(0, "tt_kart_font_rodan_ntlg_pro_b.brfnt");
        }
        break;
    }
    switch (SCGetLanguage()) {
    case SC_LANG_KOREAN:
        initFont(1, "kart_font_korea.brfnt");
        break;
    default:
        initFont(1, "kart_kanji_font.brfnt");
        break;
    }
    initFont(2, "tt_kart_extension_font.brfnt");
    initFont(3, "indicator_font.brfnt");
    initFont(4, "mario_font_number_nocolor.brfnt");
    initFont(5, "mario_font_number_outline.brfnt");
}

void FontManager::initFont(u32 index, const char *file) {
    m_fonts[index] = new Font;
    m_fonts[index]->load(file);
}

} // namespace UI
