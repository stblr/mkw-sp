#include "LanguageSelectPage.hh"

#include <sp/settings/Language.hh>

#include <cstdio>

namespace UI {

LanguageSelectPage::LanguageSelectPage() = default;

LanguageSelectPage::~LanguageSelectPage() = default;

void LanguageSelectPage::onInit() {
    m_inputManager.init(0x1, false);
    setInputManager(&m_inputManager);
    m_inputManager.setWrappingMode(MultiControlInputManager::WrappingMode::Both);

    initChildren(m_buttons.size());
    for (size_t i = 0; i < m_buttons.size(); i++) {
        insertChild(i, &m_buttons[i], 0);
    }

    for (size_t i = 0; i < m_buttons.size(); i++) {
        char variant[0x20];
        snprintf(variant, std::size(variant), "Button%zu", i);
        m_buttons[i].load("button", "LanguageSelectButton", variant, 0x1, false, false);
    }

    for (size_t i = 0; i < m_buttons.size(); i++) {
        m_buttons[i].setFrontHandler(&m_onButtonFront, false);
    }

    for (size_t i = 0; i < m_buttons.size(); i++) {
        m_buttons[i].m_index = i;
    }

    for (size_t i = 0; i < m_buttons.size(); i++) {
        MessageInfo info{};
        info.strings[0] = SP::Language::GetName(static_cast<SP::GlobalSettings::Language>(i));
        m_buttons[i].setMessageAll(6602, &info);
    }

    auto language = SP::GlobalSettings::Get<SP::GlobalSettings::Setting::Language>();
    if (language == SP::GlobalSettings::Language::Unspecified) {
        language = SP::Language::GetDefault();
    }
    m_buttons[static_cast<u32>(language)].selectDefault(0);
}

void LanguageSelectPage::onButtonFront(PushButton *button, u32 /* localPlayerId */) {
    auto language = static_cast<SP::GlobalSettings::Language>(button->m_index);
    SP::GlobalSettings::Set<SP::GlobalSettings::Setting::Language>(language);
    changeSection(SectionId::TitleFromBoot, Anim::Next, button->getDelay());
}

} // namespace UI
