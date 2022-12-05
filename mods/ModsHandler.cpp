#include "pch-il2cpp.h"
#include "ModsHandler.h"
#include "utility.h"
#include "logger.h"

#include "TownOfHost.h"
#include "TownOfHost_Y.h"
#include "TownOfHost-TheOtherRoles.h"
#include "TheOtherRoles.h"

namespace Mods {

    std::unique_ptr<ModBase> current = nullptr;
    Game::PlayerId moddedHost = 0;

    ModBase* Current() { return current.get(); }

    bool isActive() { return current != nullptr; }

    void OnPlayerLeft(Game::PlayerId player) {
        if (isActive() and player == moddedHost) {
            current.reset();
        }
    }

    void onGameEnd() {
        current.reset();
    }

    bool HandleRpc(PlayerControl* sender, uint8_t callId, MessageReader* reader) {
        if (current != nullptr) {
            try {
                current->HandleRpc(sender, callId, reader);
            }
            catch (const std::exception& ex) {
                LOG_ERROR(ex.what());
            }
            return false;
        }

        try {
            if (callId == 60) {
                // TOH or TOH:TOR VersionCheck
                if (!IsHost(sender))
                    return false; // ignore

                if (app::MessageReader_get_BytesRemaining(reader, nullptr) < 4)
                    return false; // TheOtherRoles ?

                auto pVersion = app::MessageReader_ReadString(reader, nullptr);
                app::Version* ver = app::Version_Parse(pVersion, nullptr);
                if (!ver) return false;

                std::string tag = convert_from_string(app::MessageReader_ReadString(reader, nullptr));
                if (ver->fields._Major >= 3) {
                    // only for TOH v3.0.0+
                    if (app::MessageReader_get_BytesRemaining(reader, nullptr) > 0) {
                        const auto& modForkId = convert_from_string(app::MessageReader_ReadString(reader, nullptr));
                        if (modForkId == "OriginalTOH")
                            current.reset(new TOH(ver, tag));
                        else if (modForkId == "TOH_Y")
                            current.reset(new TOH_Y(ver, tag));
                        else {
                            STREAM_DEBUG("Unknown TOH Version:" << convert_from_string(pVersion) << ", tag:" << tag << ", fork:" << modForkId);
                            return false;
                        }
                    } else {
                        // TOH:TOR < v0.7
                        //current.reset(new TOH_TOR(ver, tag));
                        STREAM_DEBUG("Unknown TOH:TOR Version:" << convert_from_string(pVersion) << ", tag:" << tag);
                        return false;
                    }
                }
                else {
                    // TOH:TOR v0.9.x.x
                    current.reset(new TOH_TOR(ver, tag));
                }
                moddedHost = sender->fields.PlayerId;
                return true;
            }
            else if (callId == 66) {
                // TheOtherRoles VersionHandshake
                if (!IsHost(sender))
                    return false; // ignore

                if (app::MessageReader_get_BytesRemaining(reader, nullptr) < 8)
                    return false; // Unknown

                int major = app::MessageReader_ReadByte(reader, nullptr);
                int minor = app::MessageReader_ReadByte(reader, nullptr);
                int patch = app::MessageReader_ReadByte(reader, nullptr);
                float timer = app::MessageReader_ReadSingle(reader, nullptr);
                int versionOwnerId = app::MessageReader_ReadPackedInt32(reader, nullptr);
                current.reset(new TOR(major, minor, patch));
                moddedHost = sender->fields.PlayerId;
                return true;
            }
        }
        catch (const std::exception& ex) {
            LOG_ERROR(ex.what());
        }
        return false;
    }

    app::Color ModBase::GetRoleColor(Game::PlayerId player) const {
        if (IsImpostorTeam(player)) {
            return Palette__TypeInfo->static_fields->ImpostorRed;
        }
        else {
            return Palette__TypeInfo->static_fields->White;
        }
    }

    std::string ModBase::GetRoleName(Game::PlayerId player) const {
        return _GetRoleName(_assignedRoles[player]);
    }

    std::string ModBase::GetSubRoleName(Game::PlayerId player) const {
        if (auto role = _assignedSubRoles[player]) {
            return _GetRoleName(_assignedSubRoles[player]);
        }
        else {
            return std::string();
        }
    }

    std::string ModBase::GetDeathReason(Game::PlayerId player) const {
        DeathReasonId reason = this->_deadPlayers[player];
        return std::format("{}", reason);
    }

    Color GetRoleColor(GameData_PlayerInfo* info) {
        if (current != nullptr) {
            return current->GetRoleColor(info->fields.PlayerId);
        }
        else {
            return ::GetRoleColor(info->fields.Role);
        }
    }

    std::string GetRoleName(GameData_PlayerInfo* info, bool abbreviated /*false*/) {
        if (current != nullptr) {
            const std::string& name = current->GetRoleName(info->fields.PlayerId);
            const std::string& subName = current->GetSubRoleName(info->fields.PlayerId);
            if (subName.empty()) {
                return name;
            }
            else {
                return name + "+" + subName;
            }
        }
        return ::GetRoleName(info->fields.Role, abbreviated);
    }
}