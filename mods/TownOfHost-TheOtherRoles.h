#pragma once
#include "TownOfHost.h"

namespace Mods {
    class TOH_TOR : public TOH {
    public:
        TOH_TOR(app::Version* version, std::string_view tag) noexcept(false);
        virtual Mod GetMod() const override;
        virtual void HandleRpc(PlayerControl* sender, uint8_t callId, MessageReader* reader) override;

        virtual bool IsImpostor(Game::PlayerId player) const override;
        virtual bool IsCrewmate(Game::PlayerId player) const override;
        virtual bool IsImpostorTeam(Game::PlayerId player) const override;

        virtual Color GetRoleColor(Game::PlayerId player) const override;

        virtual std::string GetDeathReason(Game::PlayerId player) const override;

        virtual bool IsMadmate(Game::PlayerId player) const override;
        virtual bool IsNeutral(Game::PlayerId player) const override;

        virtual bool IsCoven(Game::PlayerId player) const;

    protected:
        virtual std::string _GetRoleName(RoleId role) const override;
    };
}