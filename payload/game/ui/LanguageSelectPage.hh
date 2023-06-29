#pragma once

#include "game/ui/Button.hh"
#include "game/ui/Page.hh"

namespace UI {

class LanguageSelectPage : public Page {
public:
    LanguageSelectPage();
    LanguageSelectPage(const LanguageSelectPage &) = delete;
    LanguageSelectPage(LanguageSelectPage &&) = delete;
    ~LanguageSelectPage() override;

    void onInit() override;

private:
    void onBack(u32 localPlayerId);
    void onButtonFront(PushButton *button, u32 localPlayerId);
    void onBackButtonFront(PushButton *button, u32 localPlayerId);

    template <typename T>
    using H = typename T::template Handler<LanguageSelectPage>;

    MultiControlInputManager m_inputManager;
    std::array<PushButton, 11> m_buttons;
    H<PushButton> m_onButtonFront{this, &LanguageSelectPage::onButtonFront};
};

} // namespace UI
