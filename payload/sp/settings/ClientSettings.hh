#pragma once

#include "sp/settings/Settings.hh"

namespace SP::ClientSettings {

enum class Setting {
    // Race
    DriftMode,
    VanillaMode,
    FOV169,
    PlayerTags,
    HUDLabels,
    MapIcons,
    InputDisplay,
    RankControl,

    // Sound
    ItemMusic,
    LastLapJingle,
    LastLapSpeedup,

    // TA
    TAClass,
    TAGhostSorting,
    TAGhostTagVisibility,
    TAGhostTagContent,
    TASolidGhosts,
    TAGhostSound,

    // License
    MiiAvatar,
    MiiClient,
    LoadingScreenColor,
    PageTransitions,
};

enum class Category {
    Race,
    Sound,
    TA,
    License,
};

enum class DriftMode {
    Manual,
    Auto,
};

enum class VanillaMode {
    Disable,
    Enable,
};

enum class FOV169 {
    FOV169,
    FOV43,
};

enum class HUDLabels {
    Hide,
    Show,
};

enum class MapIcons {
    Characters,
    Miis,
};

enum class InputDisplay {
    Disable,
    Simple,
};

enum class RankControl {
    GPVS,
    Always,
};

enum class ItemMusic {
    None,
    DamageOnly,
    All,
};

enum class LastLapJingle {
    GameplayOnly,
    Always,
};

enum class LastLapSpeedup {
    None,
    Static,
    Dynamic,
};

enum class TAClass {
    CC150,
    CC200,
};

enum class TAGhostSorting {
    Time,
    Date,
    Flap,
    Lap2Pace,
    Lap3Pace,
};

enum class TAGhostTagVisibility {
    None,
    Watched,
    All,
};

enum class TAGhostTagContent {
    Name,
    Time,
    TimeNoLeading,
    Date,
};

enum class TASolidGhosts {
    None,
    Watched,
    All,
};

enum class TAGhostSound {
    None,
    Watched,
    All,
};

enum class PageTransitions {
    Disable,
    Enable,
};

typedef Settings::Group<Category> Group;
typedef Settings::Entry<Category> Entry;
template <Setting S>
using Helper = Settings::Helper<Setting, S>;

extern const char name[];
constexpr auto categoryNames = magic_enum::enum_names<Category>();
extern const u32 categoryMessageIds[];
constexpr u32 entryCount = magic_enum::enum_count<Setting>();
extern const Entry entries[];
constexpr Group group{ name, categoryNames.data(), categoryMessageIds, entryCount, entries };

typedef Settings::Settings<Category, ClientSettings::group> Settings;

} // namespace SP::ClientSettings

namespace SP::Settings {

template <>
struct Helper<ClientSettings::Setting, ClientSettings::Setting::DriftMode> {
    using type = SP::ClientSettings::DriftMode;
};

template <>
struct Helper<ClientSettings::Setting, ClientSettings::Setting::VanillaMode> {
    using type = SP::ClientSettings::VanillaMode;
};

template <>
struct Helper<ClientSettings::Setting, ClientSettings::Setting::FOV169> {
    using type = SP::ClientSettings::FOV169;
};

template <>
struct Helper<ClientSettings::Setting, ClientSettings::Setting::PlayerTags> {
    using type = u32;
};

template <>
struct Helper<ClientSettings::Setting, ClientSettings::Setting::HUDLabels> {
    using type = SP::ClientSettings::HUDLabels;
};

template <>
struct Helper<ClientSettings::Setting, ClientSettings::Setting::MapIcons> {
    using type = SP::ClientSettings::MapIcons;
};

template <>
struct Helper<ClientSettings::Setting, ClientSettings::Setting::InputDisplay> {
    using type = SP::ClientSettings::InputDisplay;
};

template <>
struct Helper<ClientSettings::Setting, ClientSettings::Setting::RankControl> {
    using type = SP::ClientSettings::RankControl;
};

template <>
struct Helper<ClientSettings::Setting, ClientSettings::Setting::ItemMusic> {
    using type = SP::ClientSettings::ItemMusic;
};

template <>
struct Helper<ClientSettings::Setting, ClientSettings::Setting::LastLapJingle> {
    using type = SP::ClientSettings::LastLapJingle;
};

template <>
struct Helper<ClientSettings::Setting, ClientSettings::Setting::LastLapSpeedup> {
    using type = SP::ClientSettings::LastLapSpeedup;
};

template <>
struct Helper<ClientSettings::Setting, ClientSettings::Setting::TAClass> {
    using type = SP::ClientSettings::TAClass;
};

template <>
struct Helper<ClientSettings::Setting, ClientSettings::Setting::TAGhostSorting> {
    using type = SP::ClientSettings::TAGhostSorting;
};

template <>
struct Helper<ClientSettings::Setting, ClientSettings::Setting::TAGhostTagVisibility> {
    using type = SP::ClientSettings::TAGhostTagVisibility;
};

template <>
struct Helper<ClientSettings::Setting, ClientSettings::Setting::TAGhostTagContent> {
    using type = SP::ClientSettings::TAGhostTagContent;
};

template <>
struct Helper<ClientSettings::Setting, ClientSettings::Setting::TASolidGhosts> {
    using type = SP::ClientSettings::TASolidGhosts;
};

template <>
struct Helper<ClientSettings::Setting, ClientSettings::Setting::TAGhostSound> {
    using type = SP::ClientSettings::TAGhostSound;
};

template <>
struct Helper<ClientSettings::Setting, ClientSettings::Setting::MiiAvatar> {
    using type = u32;
};

template <>
struct Helper<ClientSettings::Setting, ClientSettings::Setting::MiiClient> {
    using type = u32;
};

template <>
struct Helper<ClientSettings::Setting, ClientSettings::Setting::LoadingScreenColor> {
    using type = u32;
};

template <>
struct Helper<ClientSettings::Setting, ClientSettings::Setting::PageTransitions> {
    using type = SP::ClientSettings::PageTransitions;
};

}
