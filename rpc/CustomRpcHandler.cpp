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

namespace TOHTOR {
	enum CustomRPC
	{
		VersionCheck = 60,
		SyncCustomSettings = 80,
		SetDeathReason,
		EndGame,
		PlaySound,
		SetCustomRole,
		SetBountyTarget,
		SetKillOrSpell,
		SetKillOrSilence,
		SetSheriffShotLimit,
		SetTimeThiefKillCount,
		SetDousedPlayer,
		AddNameColorData,
		RemoveNameColorData,
		ResetNameColorData,
		DoSpell,
		DoSilence,
		SniperSync,
		SetLoversPlayers,
		SetExecutionerTarget,
		RemoveExecutionerTarget,
		SetGATarget,
		RemoveGATarget,
		SendFireWorksState,
		SetCurrentDousingTarget,
		SetCurrentInfectingTarget,
		SetCurrentHexingTarget,
		ToggleCamouflagueActive,
		// FIX SOME CLIENT ISSUES //
		SendBadId,
		SendGoodId,
		SetVeteranAlert,
		SetMedusaInfo,
		SetHackerProgress,
		SetPirateProgress,
		SeeredPlayer,
		SetVultureAmount,
		UpdateGA,
		NotifyDemoKill,
		SendSurvivorInfo,
		SetInfectedPlayer,
		SetHexedPlayer,
		SetTransportNumber,
		RpcMurderPlayer,
		AssassinKill,
		SetTraitor,
		RpcAddOracleTarget,
		RpcClearOracleTargets,
		SetNumOfWitchesRemaining,
		RpcSetCleanerClean
	};

	enum CustomRoles
	{
		//Default
		Crewmate = 0,
		//Impostor(Vanilla)
		Impostor,
		Shapeshifter,
		Morphling,
		Mechanic,
		Physicist,
		Target,
		//Impostor
		BountyHunter,
		VoteStealer,
		FireWorks,
		Mafia,
		SerialKiller,
		//ShapeMaster,
		Sniper,
		Vampire,
		Vampress,
		Witch,
		Warlock,
		Mare,
		Miner,
		Consort,
		YingYanger,
		Grenadier,
		Disperser,
		Puppeteer,
		TimeThief,
		Silencer,
		Ninja,
		Swooper,
		Camouflager,
		Freezer,
		Cleaner,
		EvilGuesser,
		LastImpostor,
		//Madmate
		MadGuardian,
		Madmate,
		MadSnitch,
		CrewPostor,
		CorruptedSheriff,
		SKMadmate,
		Parasite,
		MSchrodingerCat,
		// VANILLA
		Engineer,
		GuardianAngel,
		Scientist,
		//Crewmate
		Alturist,
		Lighter,
		Medium,
		Demolitionist,
		Bastion,
		NiceGuesser,
		Escort,
		Crusader,
		Psychic,
		Mystic,
		Swapper,
		Mayor,
		SabotageMaster,
		Oracle,
		Medic,
		Bodyguard,
		Sheriff,
		Investigator,
		Snitch,
		Transporter,
		SpeedBooster,
		Trapper,
		Dictator,
		Doctor,
		Child,
		Veteran,
		CSchrodingerCat,
		//Neutral
		Arsonist,
		Egoist,
		PlagueBearer,
		Pestilence,
		Vulture,
		TheGlitch,
		Postman,
		Werewolf,
		NeutWitch,
		Marksman,
		GuardianAngelTOU,
		EgoSchrodingerCat,
		Jester,
		Amnesiac,
		Hacker,
		PoisonMaster,
		BloodKnight,
		Hitman,
		Phantom,
		Pirate,
		Juggernaut,
		Opportunist,
		Survivor,
		SchrodingerCat,
		Terrorist,
		Executioner,
		Jackal,
		Sidekick,
		JSchrodingerCat,
		//HideAndSeek
		HASFox,
		HASTroll,
		//GM
		//coven
		Coven,
		Poisoner,
		CovenWitch,
		HexMaster,
		PotionMaster,
		Medusa,
		Mimic,
		Necromancer,
		Conjuror,

		// NEW GAMEMODE ROLES //
		Painter,
		Janitor,
		Supporter,

		// RANDOM ROLE HELPERS //
		LoversWin,
		// Sub-roles are After 500. Meaning, all roles under this are Modifiers.
		NoSubRoleAssigned = 500,

		// GLOBAL MODIFIERS //
		Lovers,
		LoversRecode,
		Flash, // DONE
		Escalation,
		TieBreaker, // DONE
		Oblivious, // DONE
		Sleuth, // DONE
		Watcher, // DONE
		Obvious,

		// CREW MODIFIERS //
		Bewilder, // DONE
		Bait, // DONE
		Torch, // DONE
		Diseased,

		// TAG COLORS //
		sns1,
		sns2,
		sns3,
		sns4,
		sns5,
		sns6,
		sns7,
		sns8,
		rosecolor,
		// random //
		thetaa,
		eevee,
		serverbooster,
		// SELF //
		minaa,
		// end random //
		psh1,
		psh2,
		psh3,
		psh4,
		psh5,
		psh6,
		psh7,
		psh8,
		psh9,
	};

	enum DeathReason
	{
		Kill,
		Vote,
		Suicide,
		Spell,
		LoversSuicide,
		Bite,
		Bombed,
		Misfire,
		Torched,
		Sniped,
		Execution,
		Disconnected,
		Fell,
		Alive,
		EarDamage,
		Screamed,
		etc = -1
	};

	bool IsImpostor(CustomRoles role) {
		return role >= TOHTOR::CustomRoles::Impostor && role <= TOHTOR::CustomRoles::LastImpostor;
	}

	bool IsMadmate(CustomRoles role) {
		return role >= TOHTOR::CustomRoles::MadGuardian && role <= TOHTOR::CustomRoles::MSchrodingerCat;
	}

	bool IsImpostorTeam(CustomRoles role) {
		return IsImpostor(role) || IsMadmate(role);
	}

	bool IsNeutral(CustomRoles role) {
		return role >= TOHTOR::CustomRoles::Arsonist && role <= TOHTOR::CustomRoles::HASTroll;
	}

	bool IsCoven(CustomRoles role) {
		return role >= TOHTOR::CustomRoles::Coven && role <= TOHTOR::CustomRoles::Conjuror;
	}

	bool IsCrewmate(CustomRoles role) {
		return !IsImpostorTeam(role) && !IsNeutral(role) && !IsCoven(role);
	}
}

Color GetRoleColor(GameData_PlayerInfo* info) {
	if (State.isTOH) {
		TOH::CustomRoles role = (TOH::CustomRoles)State.assignedModRoles[info->fields.PlayerId].first;
		if (TOH::IsImpostorTeam(role)) {
			return Palette__TypeInfo->static_fields->ImpostorRed;
		}
		else if (TOH::IsNeutral(role)) {
			return Palette__TypeInfo->static_fields->Orange;
		}
		else {
			return Palette__TypeInfo->static_fields->White;
		}
	}
	else if (State.isTOH_TOR) {
		TOHTOR::CustomRoles role = (TOHTOR::CustomRoles)State.assignedModRoles[info->fields.PlayerId].first;
		if (TOHTOR::IsImpostorTeam(role)) {
			return Palette__TypeInfo->static_fields->ImpostorRed;
		}
		else if (TOHTOR::IsNeutral(role)) {
			return Palette__TypeInfo->static_fields->Orange;
		}
		else if (TOHTOR::IsCoven(role)) {
			return Palette__TypeInfo->static_fields->Purple;
		}
		else {
			return Palette__TypeInfo->static_fields->White;
		}
	}
	else {
		return GetRoleColor(info->fields.Role);
	}
}

std::string GetRoleName(GameData_PlayerInfo* info, bool abbreviated) {
	if (State.isTOH) {
		//if ((*Game::pLocalPlayer)->fields.PlayerId == info->fields.PlayerId)
		//	return "";
		const auto& p = State.assignedModRoles[info->fields.PlayerId];
		TOH::CustomRoles role = (TOH::CustomRoles)p.first;
		TOH::CustomRoles role2 = (TOH::CustomRoles)p.second;
		switch (role) {
		case TOH::BountyHunter:
			return "赏金猎人";
		case TOH::EvilWatcher:
			return "邪恶的窥视者";
		case TOH::FireWorks:
			return "烟花商人";
		case TOH::Mafia:
			return "黑手党";
		case TOH::SerialKiller:
			return "嗜血杀手";
		case TOH::Sniper:
			return "狙击手";
		case TOH::Vampire:
			return "吸血鬼";
		case TOH::Witch:
			return "女巫";
		case TOH::Warlock:
			return "术士";
		case TOH::Mare:
			return "梦魇";
		case TOH::Puppeteer:
			return "傀儡师";
		case TOH::TimeThief:
			return "蚀时者";
		case TOH::EvilTracker:
			return "邪恶的追踪者";
		case TOH::MadGuardian:
			return "背叛的守卫";
		case TOH::Madmate:
			return "叛徒";
		case TOH::MadSnitch:
			return "背叛的告密者";
		case TOH::SKMadmate:
			return "叛徒小弟";
		case TOH::MSchrodingerCat:
		case TOH::CSchrodingerCat:
		case TOH::EgoSchrodingerCat:
		case TOH::SchrodingerCat:
		case TOH::JSchrodingerCat:
			return "薛定谔的猫";
		case TOH::Watcher:
			return "窥视者";
		case TOH::Bait:
			return "诱饵";
		case TOH::Lighter:
			return "执灯人";
		case TOH::Mayor:
			return "市长";
		case TOH::NiceWatcher:
			return "正义的窥视者";
		case TOH::SabotageMaster:
			return "修理大师";
		case TOH::Sheriff:
			return "警长";
		case TOH::Snitch:
			return "告密者";
		case TOH::SpeedBooster:
			return "增速者";
		case TOH::Trapper:
			return "陷阱师";
		case TOH::Dictator:
			return "独裁者";
		case TOH::Doctor:
			return "医生";
		case TOH::Seer:
			return "灵媒";
		case TOH::Arsonist:
			return "纵火犯";
		case TOH::Egoist:
			return "野心家";
		case TOH::Jester:
			return "小丑";
		case TOH::Opportunist:
			return "投机者";
		case TOH::Terrorist:
			return "恐怖分子";
		case TOH::Executioner:
			return "处刑人";
		case TOH::Jackal:
			return "豺狼";
		case TOH::HASFox:
			return "狐狸";
		case TOH::HASTroll:
			return "猎人";
		case TOH::GM:
			return "GM管理员";
		case TOH::Lovers:
			return "恋人";
		default:
			return std::format("{},{}", (int32_t)role, (int32_t)role2);
		}
	}
	else if (State.isTOH_TOR) {
		//if ((*Game::pLocalPlayer)->fields.PlayerId == info->fields.PlayerId)
		//	return "";
		const auto& p = State.assignedModRoles[info->fields.PlayerId];
		TOHTOR::CustomRoles role = (TOHTOR::CustomRoles)p.first;
		TOHTOR::CustomRoles role2 = (TOHTOR::CustomRoles)p.second;
		switch (role) {
		case TOHTOR::BountyHunter:
			return "赏金猎人";
		case TOHTOR::FireWorks:
			return "烟花商人";
		case TOHTOR::Mafia:
			return "黑手党";
		case TOHTOR::SerialKiller:
			return "嗜血杀手";
		case TOHTOR::Sniper:
			return "狙击手";
		case TOHTOR::Vampire:
			return "吸血鬼";
		case TOHTOR::Witch:
			return "女巫";
		case TOHTOR::Warlock:
			return "术士";
		case TOHTOR::Mare:
			return "梦魇";
		case TOHTOR::Puppeteer:
			return "傀儡师";
		case TOHTOR::TimeThief:
			return "蚀时者";
		case TOHTOR::MadGuardian:
			return "背叛的守卫";
		case TOHTOR::Madmate:
			return "叛徒";
		case TOHTOR::MadSnitch:
			return "背叛的告密者";
		case TOHTOR::SKMadmate:
			return "叛徒小弟";
		case TOHTOR::MSchrodingerCat:
		case TOHTOR::CSchrodingerCat:
		case TOHTOR::EgoSchrodingerCat:
		case TOHTOR::SchrodingerCat:
		case TOHTOR::JSchrodingerCat:
			return "薛定谔的猫";
		case TOHTOR::Watcher:
			return "窥视者";
		case TOHTOR::Bait:
			return "诱饵";
		case TOHTOR::Lighter:
			return "执灯人";
		case TOHTOR::Mayor:
			return "市长";
		case TOHTOR::SabotageMaster:
			return "修理大师";
		case TOHTOR::Sheriff:
			return "警长";
		case TOHTOR::Snitch:
			return "告密者";
		case TOHTOR::SpeedBooster:
			return "增速者";
		case TOHTOR::Trapper:
			return "陷阱师";
		case TOHTOR::Dictator:
			return "独裁者";
		case TOHTOR::Doctor:
			return "医生";
		case TOHTOR::Arsonist:
			return "纵火犯";
		case TOHTOR::Egoist:
			return "野心家";
		case TOHTOR::Jester:
			return "小丑";
		case TOHTOR::Opportunist:
			return "投机者";
		case TOHTOR::Terrorist:
			return "恐怖分子";
		case TOHTOR::Executioner:
			return "处刑人";
		case TOHTOR::Jackal:
			return "豺狼";
		case TOHTOR::HASFox:
			return "狐狸";
		case TOHTOR::HASTroll:
			return "猎人";
		case TOHTOR::Lovers:
			return "恋人";
		case TOHTOR::Medium:
			return "警探";
		case TOHTOR::Child:
			return "小孩";
		default:
			return std::format("{},{}", (int32_t)role, (int32_t)role2);
		}
	}
	else {
		return GetRoleName(info->fields.Role, abbreviated);
	}
}

static void HandleTohTorRpc(PlayerControl* sender, uint8_t callId, MessageReader* reader) {
	if (!IsHost(sender))
		return; // ignore
	switch (callId) {
	case TOHTOR::SetLoversPlayers:
	{
		auto count = app::MessageReader_ReadInt32(reader, nullptr);
		STREAM_DEBUG("TOHTOR: Lovers Count:" << count);
		for (int i = 0; i < count; i++) {
			Game::PlayerId id = app::MessageReader_ReadByte(reader, nullptr);
			STREAM_DEBUG("TOHTOR:  Lover:" << ToString(id));
		}
	}
	break;
	case TOHTOR::SetCustomRole:
	{
		Game::PlayerId id = app::MessageReader_ReadByte(reader, nullptr);
		TOHTOR::CustomRoles role = (TOHTOR::CustomRoles)app::MessageReader_ReadPackedInt32(reader, nullptr);
		STREAM_DEBUG("TOHTOR: SetCustomRole:" << ToString(id) << ", Role:" << role);
		if (role < TOHTOR::NoSubRoleAssigned)
			State.assignedModRoles[id].first = (int32_t)role;
		else
			State.assignedModRoles[id].second = (int32_t)role;
	}
	break;
	case TOHTOR::SendFireWorksState:
	{
		Game::PlayerId id = app::MessageReader_ReadByte(reader, nullptr);
		int state = app::MessageReader_ReadInt32(reader, nullptr);
		STREAM_DEBUG("TOHTOR: SendFireWorksState:" << ToString(id) << ", FireWorks:" << state);
	}
	break;
	case TOHTOR::SniperSync:
	{
		Game::PlayerId id = app::MessageReader_ReadByte(reader, nullptr);
		Game::PlayerId target = app::MessageReader_ReadByte(reader, nullptr);
		STREAM_DEBUG("TOHTOR: SniperSync:" << ToString(id)
					 << ", Target:" << ToString(target));
		bool isNotify = app::MessageReader_ReadBoolean(reader, nullptr);
		if (isNotify) {
			int count = app::MessageReader_ReadInt32(reader, nullptr);
			while (count > 0) {
				Game::PlayerId id = app::MessageReader_ReadByte(reader, nullptr);
				STREAM_DEBUG("TOHTOR:   Notify:" << ToString(id));
			}
		}
		else {
			int bulletCount = app::MessageReader_ReadInt32(reader, nullptr);
			STREAM_DEBUG("TOHTOR: Bullet:" << bulletCount);
		}
	}
	break;
	case TOHTOR::SetDeathReason:
	{
		Game::PlayerId id = app::MessageReader_ReadByte(reader, nullptr);
		TOHTOR::DeathReason deathReason = (TOHTOR::DeathReason)app::MessageReader_ReadInt32(reader, nullptr);
		STREAM_DEBUG("TOHTOR: SetDeathReason:" << ToString(id) << ", Reason:" << deathReason);
	}
	break;
	case TOHTOR::SetDousedPlayer:
	{
		Game::PlayerId id = app::MessageReader_ReadByte(reader, nullptr);
		Game::PlayerId target = app::MessageReader_ReadByte(reader, nullptr);
		bool doused = app::MessageReader_ReadBoolean(reader, nullptr);
		STREAM_DEBUG("TOHTOR: SetDousedPlayer:" << ToString(id)
					 << ", Target:" << ToString(target)
					 << ", Doused:" << doused);
	}
	break;
	case TOHTOR::SetCurrentDousingTarget:
	{
		Game::PlayerId id = app::MessageReader_ReadByte(reader, nullptr);
		Game::PlayerId target = app::MessageReader_ReadByte(reader, nullptr);
		STREAM_DEBUG("TOHTOR: SetCurrentDousingTarget:" << ToString(id) << ", Target:" << ToString(target));
	}
	break;
	case TOHTOR::SetSheriffShotLimit:
	{
		Game::PlayerId SheriffId = app::MessageReader_ReadByte(reader, nullptr);
		float Limit = app::MessageReader_ReadSingle(reader, nullptr);
		STREAM_DEBUG("TOHTOR: SetSheriffShotLimit:" << ToString(SheriffId) << ", Limit:" << Limit);
	}
	break;
	case TOHTOR::SyncCustomSettings:
	{
		STREAM_DEBUG("TOHTOR: SyncCustomSettings");
	}
	break;
	case TOHTOR::SetExecutionerTarget:
	{
		Game::PlayerId ExecutionerId = app::MessageReader_ReadByte(reader, nullptr);
		Game::PlayerId TargetId = app::MessageReader_ReadByte(reader, nullptr);
		STREAM_DEBUG("TOHTOR: SetExecutionerTarget:" << ToString(ExecutionerId) << ", TargetId:" << ToString(TargetId));
	}
	break;
	case TOHTOR::RemoveExecutionerTarget:
	{
		Game::PlayerId ExecutionerId = app::MessageReader_ReadByte(reader, nullptr);
		STREAM_DEBUG("TOHTOR: RemoveExecutionerTarget:" << ToString(ExecutionerId));
	}
	break;
	case TOHTOR::SetBountyTarget:
	{
		Game::PlayerId bountyId = app::MessageReader_ReadByte(reader, nullptr);
		Game::PlayerId targetId = app::MessageReader_ReadByte(reader, nullptr);
		STREAM_DEBUG("TOHTOR: SetBountyTarget:" << ToString(bountyId) << ", TargetId:" << ToString(targetId));
	}
	break;
	default:
		if (callId > 60)
			STREAM_DEBUG("Unknown RPC:" << (int)callId);
		break;
	}
}

static void HandleTohRpc(PlayerControl* sender, uint8_t callId, MessageReader* reader) {
	if (!IsHost(sender))
		return; // ignore
	switch (callId) {
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
		if (role < TOH::NoSubRoleAssigned)
			State.assignedModRoles[id].first = (int32_t)role;
		else
			State.assignedModRoles[id].second = (int32_t)role;
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
	case TOH::SetExecutionerTarget:
	{
		Game::PlayerId ExecutionerId = app::MessageReader_ReadByte(reader, nullptr);
		Game::PlayerId TargetId = app::MessageReader_ReadByte(reader, nullptr);
		STREAM_DEBUG("TOH: SetExecutionerTarget:" << ToString(ExecutionerId) << ", TargetId:" << ToString(TargetId));
	}
	break;
	case TOH::RemoveExecutionerTarget:
	{
		Game::PlayerId ExecutionerId = app::MessageReader_ReadByte(reader, nullptr);
		STREAM_DEBUG("TOH: RemoveExecutionerTarget:" << ToString(ExecutionerId));
	}
	break;
	case TOH::SetBountyTarget:
	{
		Game::PlayerId bountyId = app::MessageReader_ReadByte(reader, nullptr);
		Game::PlayerId targetId = app::MessageReader_ReadByte(reader, nullptr);
		STREAM_DEBUG("TOH: SetBountyTarget:" << ToString(bountyId) << ", TargetId:" << ToString(targetId));
	}
	break;
	default:
		if (callId > 60)
			STREAM_DEBUG("Unknown RPC:" << (int)callId);
		break;
	}
}

void HandleRpc(PlayerControl* sender, uint8_t callId, MessageReader* reader) {
	LOG_ASSERT(sender != nullptr);
	if (State.isTOH) {
		return HandleTohRpc(sender, callId, reader);
	}
	else if (State.isTOH_TOR) {
		return HandleTohTorRpc(sender, callId, reader);
	}
	else if (callId == 60) { // TOH or TOH:TOR VersionCheck
		if (!IsHost(sender))
			return; // ignore
		auto pVersion = app::MessageReader_ReadString(reader, nullptr);
		app::Version* ver = app::Version_Parse(pVersion, nullptr);
		if (!ver) return;

		std::ostringstream ss;
		ss << "MOD Version:" << convert_from_string(pVersion);
		app::MessageReader_ReadString(reader, nullptr);//skip Tag
		if (ver->fields._Major >= 3) {
			// only for TOH v3.0.0+
			try {
				const auto& modForkId = convert_from_string(app::MessageReader_ReadString(reader, nullptr));
				State.isTOH = (modForkId == "OriginalTOH");
				if (!State.isTOH)
					ss << ", ForkId:" << modForkId;
			}
			catch (...) {
				// TOH:TOR < v0.7
				State.isTOH_TOR = true;
			}
		}
		else {
			// TOH:TOR v0.9.x.x
			State.isTOH_TOR = true;
		}
		LOG_DEBUG(ss.str());
		return;
	}
			
	switch (callId) {
	case 85://(uint8_t)42069:
	{
		uint8_t playerid = MessageReader_ReadByte(reader, NULL);
		if (playerid != sender->fields.PlayerId) {
			// from mod
			break;
		}
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