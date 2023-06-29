#pragma once

#include "game/ui/Page.hh"

namespace UI {

class TitlePage : public Page {
public:
    void REPLACED(onInit)();
    REPLACE void onInit() override;
    void REPLACED(onActivate)();
    REPLACE void onActivate() override;
    void REPLACED(afterCalc)();
    REPLACE void afterCalc() override;

private:
    u8 _044[0x053 - 0x044];
    bool m_geckoWarningShown; // Was padding
    u8 _054[0x33c - 0x054];
    bool m_replacementRequested;
    u8 _33d[0x348 - 0x33d];
    bool m_useAlternativeBackgrounds;
    u8 _349[0x34c - 0x349];
    u32 m_alternativeBackground;
};
static_assert(sizeof(TitlePage) == 0x350);

} // namespace UI
