#include "pch-il2cpp.h"
#include "TheOtherRoles.h"
#include "utility.h"
#include "logger.h"

namespace Mods {
	namespace v420 {
		enum class CustomRPC
		{
			// Main Controls

			ResetVaribles = 60,
			ShareOptions,
			ForceEnd,
			WorkaroundSetRoles,
			SetRole,
			SetModifier,
			VersionHandshake,
			UseUncheckedVent,
			UncheckedMurderPlayer,
			UncheckedCmdReportDeadBody,
			UncheckedExilePlayer,
			DynamicMapOption,
			SetGameStarting,
			ShareGamemode,

			// Role functionality

			EngineerFixLights = 101,
			EngineerFixSubmergedOxygen,
			EngineerUsedRepair,
			CleanBody,
			MedicSetShielded,
			ShieldedMurderAttempt,
			TimeMasterShield,
			TimeMasterRewindTime,
			ShifterShift,
			SwapperSwap,
			MorphlingMorph,
			CamouflagerCamouflage,
			TrackerUsedTracker,
			VampireSetBitten,
			PlaceGarlic,
			DeputyUsedHandcuffs,
			DeputyPromotes,
			JackalCreatesSidekick,
			SidekickPromotes,
			ErasePlayerRoles,
			SetFutureErased,
			SetFutureShifted,
			SetFutureShielded,
			SetFutureSpelled,
			PlaceNinjaTrace,
			PlacePortal,
			UsePortal,
			PlaceJackInTheBox,
			LightsOut,
			PlaceCamera,
			SealVent,
			ArsonistWin,
			GuesserShoot,
			VultureWin,
			LawyerSetTarget,
			LawyerPromotesToPursuer,
			SetBlanked,
			Bloody,
			SetFirstKill,
			Invert,
			SetTiebreak,
			SetInvisible,
			ThiefStealsRole,
			SetTrap,
			TriggerTrap,

			// Gamemode
			SetGuesserGm,
			HuntedShield,
			HuntedRewindTime,
			ShareTimer
		};
		enum class RoleId {
			Jester,
			Mayor,
			Portalmaker,
			Engineer,
			Sheriff,
			Deputy,
			Lighter,
			Godfather,
			Mafioso,
			Janitor,
			Detective,
			TimeMaster,
			Medic,
			Swapper,
			Seer,
			Morphling,
			Camouflager,
			Hacker,
			Tracker,
			Vampire,
			Snitch,
			Jackal,
			Sidekick,
			Eraser,
			Spy,
			Trickster,
			Cleaner,
			Warlock,
			SecurityGuard,
			Arsonist,
			EvilGuesser,
			NiceGuesser,
			BountyHunter,
			Vulture,
			Medium,
			Trapper,
			Lawyer,
			Prosecutor,
			Pursuer,
			Witch,
			Ninja,
			Thief,
			Crewmate,
			Impostor,
			// Modifier ---
			Lover,
			Bait,
			Bloody,
			AntiTeleport,
			Tiebreaker,
			Sunglasses,
			Mini,
			Vip,
			Invert,
			Chameleon,
			Shifter
		};
	}

	TOR::TOR(int major, int minor, int patch) noexcept(false) {
		SetVersion(major, minor, patch, 0);
		_version = std::format("TOR Version:v{}.{}.{}",
							   major, minor, patch);
		LOG_DEBUG(this->GetVersion());
		if (!(major == 4
			  && minor == 2
			  && (patch == 0 || patch == 1))) {
			throw std::invalid_argument("Unsupported TOR");
		}
	}

	Mod TOR::GetMod() const {
        return Mod::TheOtherRoles;
    }

    void TOR::HandleRpc(PlayerControl* sender, uint8_t callId, MessageReader* reader) {
        if (!IsHost(sender))
            return; // ignore
		switch (callId) {
		case (int)v420::CustomRPC::WorkaroundSetRoles:
		{
			auto numberOfRoles = app::MessageReader_ReadByte(reader, nullptr);
			for (int i = 0; i < numberOfRoles; i++) {
				auto id = (Game::PlayerId)app::MessageReader_ReadPackedUInt32(reader, nullptr);
				RoleId role = app::MessageReader_ReadPackedUInt32(reader, nullptr);
				if (role < (RoleId)v420::RoleId::Lover)
					this->_assignedRoles[id] = role;
				else
					this->_assignedSubRoles[id] = role;
				STREAM_DEBUG("TOR: WorkaroundSetRoles:" << ToString(id) << ", Role:" << this->_GetRoleName(role));
			}
		}
		break;
		case (int)v420::CustomRPC::SetRole:
		{
			auto role = app::MessageReader_ReadByte(reader, nullptr);
			auto id = app::MessageReader_ReadByte(reader, nullptr);
			STREAM_DEBUG("TOR: SetRole:" << ToString(id) << ", Role:" << (int)role);
		}
		break;
		default:
			if (callId > 60)
				STREAM_DEBUG("Unknown RPC:" << (int)callId);
			break;
		}
    }

	bool TOR::IsImpostor(Game::PlayerId player) const {
		if (auto data = GetPlayerDataById(player)) {
			return PlayerIsImpostor(data);
		}
		else {
			return false;
		}
	}
	bool TOR::IsCrewmate(Game::PlayerId player) const {
		return !IsImpostorTeam(player);
	}
	bool TOR::IsImpostorTeam(Game::PlayerId player) const {
		return IsImpostor(player);
	}

	std::string TOR::_GetRoleName(RoleId role) const {
		return std::format("{}", role);
	}
}

