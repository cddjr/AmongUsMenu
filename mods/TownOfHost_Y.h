#pragma once
#include "TownOfHost.h"

namespace Mods {
    class TOH_Y : public TOH {
    public:
        TOH_Y(app::Version* version, std::string_view tag) noexcept(false);
        virtual Mod GetMod() const override;
        virtual void HandleRpc(PlayerControl* sender, uint8_t callId, MessageReader* reader) override;

        virtual bool IsImpostor(Game::PlayerId player) const override;

        virtual Color GetRoleColor(Game::PlayerId player) const override;

        virtual std::string GetDeathReason(Game::PlayerId player) const override;

        virtual bool IsMadmate(Game::PlayerId player) const override;
        virtual bool IsNeutral(Game::PlayerId player) const override;

    protected:
        virtual std::string _GetRoleName(RoleId role) const override;
    };
}