#include "MultiDvdArchive.hh"

#include "game/system/ResourceManager.hh"

#include <sp/settings/GlobalSettings.hh>
#include <sp/settings/Language.hh>

extern "C" {
#include <revolution.h>
#include <stdio.h>
}

namespace System {

void MultiDvdArchive::setMission(u32 missionId) {
    m_formats[1] = Format::Single;
    snprintf(m_names[1], 0x80, "Race/MissionRun/mr%02d.szs", missionId);
}

void MultiDvdArchive::init() {
    REPLACED(init)();

    if (m_archiveCount <= 1) {
        return;
    }

    snprintf(m_names[1], 0x80, "_Dif.szs");
    m_formats[1] = Format::Double;
}

DvdArchive &MultiDvdArchive::archive(u16 i) {
    assert(i < m_archiveCount);
    return m_archives[i];
}

u16 MultiDvdArchive::count() const {
    return m_archiveCount;
}

MultiDvdArchive *MultiDvdArchive::Create(ResourceType type) {
    switch (type) {
    case ResourceType::Race:
        return new RaceMultiDvdArchive;
    case ResourceType::Course:
        return new CourseMultiDvdArchive;
    case ResourceType::Menu:
        return new MenuMultiDvdArchive;
    case ResourceType::Font:
        return new FontMultiDvdArchive;
    default:
        MultiDvdArchive *archive = new MultiDvdArchive(2);
        archive->init();
        return archive;
    }
}

RaceMultiDvdArchive::RaceMultiDvdArchive() : MultiDvdArchive(5) {
    init();
}

RaceMultiDvdArchive::~RaceMultiDvdArchive() = default;

void RaceMultiDvdArchive::init() {
    snprintf(m_names[0], 0x80, ".szs");

    if (SP::GlobalSettings::Get<SP::GlobalSettings::Setting::Language>() ==
            SP::GlobalSettings::Language::Korean) {
        snprintf(m_names[1], 0x80, "_J.szs");
    } else {
        snprintf(m_names[1], 0x80, "_%s.szs", SP::Language::GetCode());
    }

    // New archives
    snprintf(m_names[2], 0x80, "SP.szs");
    snprintf(m_names[3], 0x80, "_Dif.szs");
    snprintf(m_names[4], 0x80, "_%s_Dif.szs", SP::Language::GetCode());

    for (size_t i = 0; i < 5; i++) {
        m_formats[i] = Format::Double;
    }
}

MenuMultiDvdArchive::MenuMultiDvdArchive() : MultiDvdArchive(6) {
    init();
}

MenuMultiDvdArchive::~MenuMultiDvdArchive() = default;

void MenuMultiDvdArchive::init() {
    SP_LOG("%s", SP::Language::GetBaseCode());
    SP_LOG("%s", SP::Language::GetCode());
    if (REGION == REGION_K) {
        snprintf(m_names[0], 0x80, "_R.szs");
    } else {
        snprintf(m_names[0], 0x80, ".szs");
    }

    snprintf(m_names[1], 0x80, "_%s.szs", SP::Language::GetBaseCode());
    snprintf(m_names[2], 0x80, "SP.szs");
    snprintf(m_names[3], 0x80, "SP_%s.szs", SP::Language::GetCode());
    snprintf(m_names[4], 0x80, "_Dif.szs");
    snprintf(m_names[5], 0x80, "_%s_Dif.szs", SP::Language::GetCode());

    for (size_t i = 0; i < 6; i++) {
        m_formats[i] = Format::Double;
    }
}

FontMultiDvdArchive::FontMultiDvdArchive() : MultiDvdArchive(2) {
    init();
}

FontMultiDvdArchive::~FontMultiDvdArchive() = default;

void FontMultiDvdArchive::init() {
    snprintf(m_names[0], 0x80, "/Scene/UI/FontSP.szs");
    snprintf(m_names[1], 0x80, "/Scene/UI/Font_Dif.szs");

    for (size_t i = 0; i < 2; i++) {
        m_formats[i] = Format::Single;
    }
}

} // namespace System
