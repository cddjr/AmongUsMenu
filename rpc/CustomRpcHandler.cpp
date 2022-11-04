#include "pch-il2cpp.h"
#include "_rpc.h"
#include "game.h"
#include "state.hpp"
#include "logger.h"
namespace TOH {
	enum
	{
		VersionCheck = 60,
		RequestRetryVersionCheck = 61,
		SyncCustomSettings = 80,
		SetDeathReason,
		EndGame,
		PlaySound,
		SetCustomRole,
		SetBountyTarget,
		SetKillOrSpell,
		SetSheriffShotLimit,
		SetTimeThiefKillCount,
		SetDousedPlayer,
		AddNameColorData,
		RemoveNameColorData,
		ResetNameColorData,
		DoSpell,
		SniperSync,
		SetLoversPlayers,
		SetExecutionerTarget,
		RemoveExecutionerTarget,
		SendFireWorksState,
		SetCurrentDousingTarget,
		SetEvilTrackerTarget,
	};
	enum CustomRoles
	{
		//Default
		Crewmate = 0,
		//Impostor(Vanilla)
		Impostor,
		Shapeshifter,
		//Impostor
		BountyHunter,
		EvilWatcher,
		FireWorks,
		Mafia,
		SerialKiller,
		//ShapeMaster,
		Sniper,
		Vampire,
		Witch,
		Warlock,
		Mare,
		Puppeteer,
		TimeThief,
		EvilTracker,
		LastImpostor,
		//Madmate
		MadGuardian,
		Madmate,
		MadSnitch,
		SKMadmate,
		MSchrodingerCat,
		Watcher,
		//Crewmate(Vanilla)
		Engineer,
		GuardianAngel,
		Scientist,
		//Crewmate
		Bait,
		Lighter,
		Mayor,
		NiceWatcher,
		SabotageMaster,
		Sheriff,
		Snitch,
		SpeedBooster,
		Trapper,
		Dictator,
		Doctor,
		Seer,
		CSchrodingerCat,
		//Neutral
		Arsonist,
		Egoist,
		EgoSchrodingerCat,
		Jester,
		Opportunist,
		SchrodingerCat,
		Terrorist,
		Executioner,
		Jackal,
		JSchrodingerCat,
		//HideAndSeek
		HASFox,
		HASTroll,
		//GM
		GM,
		// Sub-roll after 500
		NoSubRoleAssigned = 500,
		Lovers,
	};

	enum DeathReason
	{
		Kill,
		Vote,
		Suicide,
		Spell,
		FollowingSuicide,
		Bite,
		Bombed,
		Misfire,
		Torched,
		Sniped,
		Execution,
		Disconnected,
		Fall,
		etc = -1
	};

	bool IsImpostor(CustomRoles role) {
		return role >= TOH::CustomRoles::Impostor && role <= TOH::CustomRoles::LastImpostor;
	}

	bool IsMadmate(CustomRoles role) {
		return role >= TOH::CustomRoles::MadGuardian && role <= TOH::CustomRoles::MSchrodingerCat;
	}

	bool IsImpostorTeam(CustomRoles role) {
		return IsImpostor(role) || IsMadmate(role);
	}

	bool IsNeutral(CustomRoles role) {
		return role >= TOH::CustomRoles::Arsonist && role <= TOH::CustomRoles::HASTroll;
	}

	bool IsCrewmate(CustomRoles role) {
		return !IsImpostorTeam(role) && !IsNeutral(role);
	}
}

void HandleRpc(uint8_t callId, MessageReader* reader) {
	switch (callId) {
	case TOH::VersionCheck:
	{
		auto pVersion = app::MessageReader_ReadString(reader, nullptr);
		app::Version* ver = app::Version_Parse(pVersion, nullptr);
		if (!ver) break;

		std::ostringstream ss;
		ss << "MOD Version:" << convert_from_string(pVersion);
		app::MessageReader_ReadString(reader, nullptr);//skip Tag
		if (ver->fields._Major >= 3) {
			// only for TOH v3.0.0+
			try {
				const auto& modForkId = convert_from_string(app::MessageReader_ReadString(reader, nullptr));
				ss << ", ForkId:" << modForkId;
				bool isTOH = (modForkId == "OriginalTOH");
			}
			catch (...) {
				// TOR < v0.7
			}
		}
		else {
			// TOR ?
		}
		LOG_DEBUG(ss.str());
	}
	break;
	case TOH::SetLoversPlayers:
	{
		auto count = app::MessageReader_ReadInt32(reader, nullptr);
		STREAM_DEBUG("TOH: Lovers Count:" << count);
		for (int i = 0; i < count; i++) {
			Game::PlayerId id = app::MessageReader_ReadByte(reader, nullptr);
			STREAM_DEBUG("TOH:  Lover:" << ToString(id));
		}
	}
	break;
	case TOH::SetCustomRole:
	{
		Game::PlayerId id = app::MessageReader_ReadByte(reader, nullptr);
		TOH::CustomRoles role = (TOH::CustomRoles)app::MessageReader_ReadPackedInt32(reader, nullptr);
		STREAM_DEBUG("TOH: SetCustomRole:" << ToString(id) << ", Role:" << role
					 << ", " << (TOH::IsImpostorTeam(role) ? "ImpostorTeam" : TOH::IsNeutral(role) ? "Neutral" : "Crewmate"));
	}
	break;
	case TOH::SendFireWorksState:
	{
		Game::PlayerId id = app::MessageReader_ReadByte(reader, nullptr);
		int state = app::MessageReader_ReadInt32(reader, nullptr);
		STREAM_DEBUG("TOH: SendFireWorksState:" << ToString(id) << ", FireWorks:" << state);
	}
	break;
	case TOH::SniperSync:
	{
		Game::PlayerId id = app::MessageReader_ReadByte(reader, nullptr);
		Game::PlayerId target = app::MessageReader_ReadByte(reader, nullptr);
		STREAM_DEBUG("TOH: SniperSync:" << ToString(id)
					 << ", Target:" << ToString(target));
		bool isNotify = app::MessageReader_ReadBoolean(reader, nullptr);
		if (isNotify) {
			int count = app::MessageReader_ReadInt32(reader, nullptr);
			while (count > 0) {
				Game::PlayerId id = app::MessageReader_ReadByte(reader, nullptr);
				STREAM_DEBUG("TOH:   Notify:" << ToString(id));
			}
		}
		else {
			int bulletCount = app::MessageReader_ReadInt32(reader, nullptr);
			STREAM_DEBUG("TOH: Bullet:" << bulletCount);
		}
	}
	break;
	case TOH::SetDeathReason:
	{
		Game::PlayerId id = app::MessageReader_ReadByte(reader, nullptr);
		TOH::DeathReason deathReason = (TOH::DeathReason)app::MessageReader_ReadInt32(reader, nullptr);
		STREAM_DEBUG("TOH: SetDeathReason:" << ToString(id) << ", Reason:" << deathReason);
	}
	break;
	case TOH::SetDousedPlayer:
	{
		Game::PlayerId id = app::MessageReader_ReadByte(reader, nullptr);
		Game::PlayerId target = app::MessageReader_ReadByte(reader, nullptr);
		bool doused = app::MessageReader_ReadBoolean(reader, nullptr);
		STREAM_DEBUG("TOH: SetDousedPlayer:" << ToString(id)
					 << ", Target:" << ToString(target)
					 << ", Doused:" << doused);
	}
	break;
	case TOH::SetCurrentDousingTarget:
	{
		Game::PlayerId id = app::MessageReader_ReadByte(reader, nullptr);
		Game::PlayerId target = app::MessageReader_ReadByte(reader, nullptr);
		STREAM_DEBUG("TOH: SetCurrentDousingTarget:" << ToString(id) << ", Target:" << ToString(target));
	}
	break;
	case TOH::SetEvilTrackerTarget:
	{
		Game::PlayerId id = app::MessageReader_ReadByte(reader, nullptr);
		Game::PlayerId target = app::MessageReader_ReadByte(reader, nullptr);
		STREAM_DEBUG("TOH: SetEvilTrackerTarget:" << ToString(id) << ", Target:" << ToString(target));
	}
	break;
	case TOH::SetSheriffShotLimit:
	{
		Game::PlayerId SheriffId = app::MessageReader_ReadByte(reader, nullptr);
		float Limit = app::MessageReader_ReadSingle(reader, nullptr);
		STREAM_DEBUG("TOH: SetSheriffShotLimit:" << ToString(SheriffId) << ", Limit:" << Limit);
	}
	break;
	case TOH::SyncCustomSettings:
	{
		STREAM_DEBUG("TOH: SyncCustomSettings");
	}
	break;
	default:
		if (callId > 60)
			STREAM_DEBUG("Unknown RPC:" << (int)callId);
		break;
	case 85://(uint8_t)42069:
	{
		uint8_t playerid = MessageReader_ReadByte(reader, NULL);
		if (!std::count(State.aumUsers.begin(), State.aumUsers.end(), playerid)) {
			State.aumUsers.push_back(playerid);
			STREAM_DEBUG("RPC Received for another AUM User from " << ToString((Game::PlayerId)playerid));
		}
	}
	break;
	case 101:
	{
		std::string playerName = convert_from_string(MessageReader_ReadString(reader, NULL));
		std::string message = convert_from_string(MessageReader_ReadString(reader, NULL));
		uint32_t colorId = MessageReader_ReadInt32(reader, NULL);
		if (message.size() == 0) break;
		State.chatMessages.emplace_back(std::make_unique<RpcChatMessage>(playerName, message, colorId, std::chrono::system_clock::now()));
		State.newChatMessage = true;
	}
	break;
	}
}