#pragma once
#include <array>
#include <memory>
#include "game.h"

namespace Mods {

    using RoleId = int32_t;
    using DeathReasonId = int32_t;

    enum class Mod {
        TownOfHost,
        TownOfHost_Y,
        TownOfHost_TheOtherRoles,
        TheOtherRoles,
    };

    bool isActive();

    bool HandleRpc(PlayerControl* sender, uint8_t callId, MessageReader* reader);

    void OnPlayerLeft(Game::PlayerId player);

    void onGameEnd();

    Color GetRoleColor(GameData_PlayerInfo* info);

    Color ToColor(std::string_view str);

    std::string GetRoleName(GameData_PlayerInfo* info, bool abbreviated = false);

    class ModBase {
        friend class ScopedModVersion;
    public:
        virtual ~ModBase() {
            _assignedRoles = {};
            _deadPlayers = {};
        }

        virtual Mod GetMod() const = 0;

        std::string GetVersion() const {
            return _version;
        }

        virtual bool IsImpostor(Game::PlayerId player) const = 0;
        virtual bool IsCrewmate(Game::PlayerId player) const = 0;
        virtual bool IsImpostorTeam(Game::PlayerId player) const = 0;

        virtual app::Color GetRoleColor(Game::PlayerId player) const;

        virtual std::string GetRoleName(Game::PlayerId player) const;
        virtual std::string GetSubRoleName(Game::PlayerId player) const;

        virtual std::string GetDeathReason(Game::PlayerId player) const;

        virtual void HandleRpc(PlayerControl* sender, uint8_t callId, MessageReader* reader) = 0;

    protected:
        void SetVersion(app::Version* version) {
            _major = version->fields._Major;
            _minor = version->fields._Minor;
            _build = version->fields._Build;
            _revision = version->fields._Revision;
        }
        void SetVersion(int major, int minor, int build, int revision) {
            _major = major;
            _minor = minor;
            _build = build;
            _revision = revision;
        }

        virtual std::string _GetRoleName(RoleId role) const = 0;

    protected:
        int _major, _minor, _build, _revision;
        std::string _version;
        std::array<RoleId, Game::MAX_PLAYERS> _assignedRoles = {};
        std::array<RoleId, Game::MAX_PLAYERS> _assignedSubRoles = {};
        std::array<DeathReasonId, Game::MAX_PLAYERS> _deadPlayers = {};
    };

    ModBase* Current();

    class ScopedModVersion {
    public:
        ScopedModVersion(int major, int minor, int build, int revision) {
            _major = Current()->_major; _minor = Current()->_minor;
            _build = Current()->_build; _revision = Current()->_revision;
            Current()->SetVersion(major, minor, build, revision);
        }
        ~ScopedModVersion() {
            Current()->SetVersion(_major, _minor, _build, _revision);
        }
    protected:
        int _major, _minor, _build, _revision;
    };
}