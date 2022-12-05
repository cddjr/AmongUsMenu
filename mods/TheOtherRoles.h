#pragma once
#include "ModsHandler.h"

namespace Mods {
    class TOR : public ModBase {
    public:
        TOR(int major, int minor, int patch) noexcept(false);
        virtual Mod GetMod() const override;
        virtual void HandleRpc(PlayerControl* sender, uint8_t callId, MessageReader* reader) override;

        virtual bool IsImpostor(Game::PlayerId player) const override;
        virtual bool IsCrewmate(Game::PlayerId player) const override;
        virtual bool IsImpostorTeam(Game::PlayerId player) const override;
    protected:
        TOR() = default;
        virtual std::string _GetRoleName(RoleId role) const override;
    };
}