#include "CtrlRaceNameBalloon.hh"

#include "game/system/RaceConfig.hh"
#include "game/system/SaveManager.hh"
#include "game/ui/SectionManager.hh"
#include "game/ui/page/RacePage.hh"

namespace UI {

void CtrlRaceNameBalloon::calcVisibility() {
    // An artificial 1 frame delay is added to match the camera.
    const auto *racePage = getPage()->downcast<RacePage>();
    assert(racePage);
    u8 lastWatchedPlayerId = racePage->lastWatchedPlayerId();

    if (!getVisible()) {
        return;
    }

    const auto &raceScenario = System::RaceConfig::Instance()->raceScenario();
    if (raceScenario.gameMode != System::RaceConfig::GameMode::TimeAttack) {
        return;
    }

    if (racePage->watchedPlayerId() != lastWatchedPlayerId) {
        setVisible(false);
        return;
    }

    auto *saveManager = System::SaveManager::Instance();
    switch (saveManager->getSetting<SP::ClientSettings::Setting::TAGhostTagVisibility>()) {
    case SP::ClientSettings::TAGhostTagVisibility::None:
        setVisible(false);
        return;
    case SP::ClientSettings::TAGhostTagVisibility::Watched:
        setVisible(m_playerId == lastWatchedPlayerId);
        return;
    default:
        return;
    }
}

void CtrlRaceNameBalloon::refreshText(u32 playerId) {
    const auto &raceScenario = System::RaceConfig::Instance()->raceScenario();
    if (raceScenario.players[playerId].type != System::RaceConfig::Player::Type::Ghost) {
        refreshTextName(playerId);
        return;
    }

    auto *saveManager = System::SaveManager::Instance();
    switch (saveManager->getSetting<SP::ClientSettings::Setting::TAGhostTagContent>()) {
    case SP::ClientSettings::TAGhostTagContent::Name:
        refreshTextName(playerId);
        break;
    case SP::ClientSettings::TAGhostTagContent::Time:
        refreshTextTime(playerId, /* leadingZeroes */ true);
        break;
    case SP::ClientSettings::TAGhostTagContent::TimeNoLeading:
        refreshTextTime(playerId, /* leadingZeroes */ false);
        break;
    case SP::ClientSettings::TAGhostTagContent::Date:
        refreshTextDate(playerId);
        break;
    }
}

void CtrlRaceNameBalloon::refreshTextName(u32 playerId) {
    MessageInfo info{};
    info.miis[0] = SectionManager::Instance()->globalContext()->m_playerMiis.get(playerId);
    setMessage("chara_name", 9501, &info);
}

void CtrlRaceNameBalloon::refreshTextTime(u32 playerId, bool leadingZeroes) {
    const auto &raceScenario = System::RaceConfig::Instance()->raceScenario();
    bool isReplay = raceScenario.players[0].type == System::RaceConfig::Player::Type::Ghost;
    u32 index = isReplay ? playerId : playerId - 1;
    auto *header = reinterpret_cast<System::RawGhostHeader *>((*raceScenario.ghostBuffer)[index]);
    MessageInfo info{};
    info.intVals[0] = header->raceTime.minutes;
    info.intVals[1] = header->raceTime.seconds;
    info.intVals[2] = header->raceTime.milliseconds;
    setMessage("chara_name", leadingZeroes ? 1400 : 10071, &info);
}

void CtrlRaceNameBalloon::refreshTextDate(u32 playerId) {
    const auto &raceScenario = System::RaceConfig::Instance()->raceScenario();
    bool isReplay = raceScenario.players[0].type == System::RaceConfig::Player::Type::Ghost;
    u32 index = isReplay ? playerId : playerId - 1;
    auto *header = reinterpret_cast<System::RawGhostHeader *>((*raceScenario.ghostBuffer)[index]);
    MessageInfo info{};
    info.intVals[0] = header->year + 2000;
    info.intVals[1] = header->month;
    info.intVals[2] = header->day;
    setMessage("chara_name", 10048, &info);
}

BalloonManager::BalloonManager() : m_namePositions(new Vec3[12]) {
    for (size_t i = 0; i < 12; i++) {
        m_namePositions[i] = {};
    }
}

BalloonManager::~BalloonManager() = default;

void BalloonManager::dt(s32 type) {
    if (type > 0) {
        delete this;
    } else {
        this->~BalloonManager();
    }
}

void BalloonManager::init(u8 localPlayerId) {
    m_localPlayerId = localPlayerId;
    for (size_t i = 0; i < std::size(m_playerIds); i++) {
        m_playerIds[i] = -1;
    }
    for (size_t i = 0; i < std::size(m_nameIsEnabled); i++) {
        m_nameIsEnabled[i] = false;
    }
}

void BalloonManager::addNameControl(CtrlRaceNameBalloon *UNUSED(nameControl)) {
    m_nameCount++;
}

void BalloonManager::calc() {
    const auto &raceScenario = System::RaceConfig::Instance()->raceScenario();
    if (raceScenario.gameMode != System::RaceConfig::GameMode::TimeAttack) {
        auto *saveManager = System::SaveManager::Instance();
        u32 totalNameCount = saveManager->getSetting<SP::ClientSettings::Setting::PlayerTags>();
        u32 localPlayerCount = raceScenario.localPlayerCount;
        if (localPlayerCount == 0) {
            localPlayerCount = 1;
        }
        u32 nameCount = totalNameCount / localPlayerCount;
        nameCount += m_localPlayerId < (totalNameCount % localPlayerCount);
        if (nameCount != m_nameCount) {
            for (u32 i = 0; i < m_nameCount; i++) {
                m_playerIds[i] = -1;
                m_nameIsEnabled[i] = false;
            }
            m_nameCount = nameCount;
        }
    }

    REPLACED(calc)();
}

} // namespace UI
