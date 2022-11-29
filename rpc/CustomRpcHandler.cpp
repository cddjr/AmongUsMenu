#include "pch-il2cpp.h"
#include "_rpc.h"
#include "game.h"
#include "state.hpp"
#include "logger.h"

// v3.0.2
namespace TOH {
	enum CustomRPC
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

	std::string GetRoleName(CustomRoles role) {
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
			return std::format("{}", (int32_t)role);
		}
	}

	std::string GetDeathReason(DeathReason reason) {
		switch (reason) {
		case DeathReason::Kill:
			return "被杀";
		case DeathReason::Vote:
			return "放逐";
		case DeathReason::Suicide:
			return "自杀";
		case DeathReason::Spell:
			return "咒杀";
		case DeathReason::FollowingSuicide:
			return "为爱而死";
		case DeathReason::Bite:
			return "吸血";
		case DeathReason::Bombed:
			return "炸死";
		case DeathReason::Misfire:
			return "走火";
		case DeathReason::Torched:
			return "烧死";
		case DeathReason::Sniped:
			return "狙杀";
		case DeathReason::Execution:
			return "处刑";
		case DeathReason::Disconnected:
			return "断连";
		case DeathReason::Fall:
			return "摔死";
		case DeathReason::etc:
			return "其他";
		default:
			return std::format("{}", (int32_t)reason);
		}
	}

	void HandleRpc(PlayerControl* sender, uint8_t callId, MessageReader* reader) {
		if (!IsHost(sender))
			return; // ignore
		switch ((CustomRPC)callId) {
		case SetLoversPlayers:
		{
			auto count = app::MessageReader_ReadInt32(reader, nullptr);
			STREAM_DEBUG("TOH: Lovers Count:" << count);
			while (count-- > 0) {
				Game::PlayerId id = app::MessageReader_ReadByte(reader, nullptr);
				STREAM_DEBUG("TOH:  Lover:" << ToString(id));
			}
		}
		break;
		case SetCustomRole:
		{
			Game::PlayerId id = app::MessageReader_ReadByte(reader, nullptr);
			CustomRoles role = (CustomRoles)app::MessageReader_ReadPackedInt32(reader, nullptr);
			STREAM_DEBUG("TOH: SetCustomRole:" << ToString(id) << ", Role:" << GetRoleName(role)
						 << ", " << (IsImpostorTeam(role) ? "ImpostorTeam" :
									 IsNeutral(role) ? "Neutral" : "Crewmate"));
			if (role < NoSubRoleAssigned)
				State.assignedModRoles[id].first = (int32_t)role;
			else
				State.assignedModRoles[id].second = (int32_t)role;
		}
		break;
		case SendFireWorksState:
		{
			Game::PlayerId id = app::MessageReader_ReadByte(reader, nullptr);
			int state = app::MessageReader_ReadInt32(reader, nullptr);
			STREAM_DEBUG("TOH: SendFireWorksState:" << ToString(id) << ", FireWorks:" << state);
		}
		break;
		case SniperSync:
		{
			Game::PlayerId id = app::MessageReader_ReadByte(reader, nullptr);
			Game::PlayerId target = app::MessageReader_ReadByte(reader, nullptr);
			STREAM_DEBUG("TOH: SniperSync:" << ToString(id)
						 << ", Target:" << ToString(target));
			bool isNotify = app::MessageReader_ReadBoolean(reader, nullptr);
			if (isNotify) {
				int count = app::MessageReader_ReadInt32(reader, nullptr);
				while (count-- > 0) {
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
		case SetDeathReason:
		{
			Game::PlayerId id = app::MessageReader_ReadByte(reader, nullptr);
			DeathReason deathReason = (DeathReason)app::MessageReader_ReadInt32(reader, nullptr);
			STREAM_DEBUG("TOH: SetDeathReason:" << ToString(id) << ", Reason:" << GetDeathReason(deathReason));
		}
		break;
		case SetDousedPlayer:
		{
			Game::PlayerId id = app::MessageReader_ReadByte(reader, nullptr);
			Game::PlayerId target = app::MessageReader_ReadByte(reader, nullptr);
			bool doused = app::MessageReader_ReadBoolean(reader, nullptr);
			STREAM_DEBUG("TOH: SetDousedPlayer:" << ToString(id)
						 << ", Target:" << ToString(target)
						 << ", Doused:" << doused);
		}
		break;
		case SetCurrentDousingTarget:
		{
			Game::PlayerId id = app::MessageReader_ReadByte(reader, nullptr);
			Game::PlayerId target = app::MessageReader_ReadByte(reader, nullptr);
			STREAM_DEBUG("TOH: SetCurrentDousingTarget:" << ToString(id) << ", Target:" << ToString(target));
		}
		break;
		case SetEvilTrackerTarget:
		{
			Game::PlayerId id = app::MessageReader_ReadByte(reader, nullptr);
			Game::PlayerId target = app::MessageReader_ReadByte(reader, nullptr);
			STREAM_DEBUG("TOH: SetEvilTrackerTarget:" << ToString(id) << ", Target:" << ToString(target));
		}
		break;
		case SetSheriffShotLimit:
		{
			Game::PlayerId SheriffId = app::MessageReader_ReadByte(reader, nullptr);
			float Limit = app::MessageReader_ReadSingle(reader, nullptr);
			STREAM_DEBUG("TOH: SetSheriffShotLimit:" << ToString(SheriffId) << ", Limit:" << Limit);
		}
		break;
		case SyncCustomSettings:
		{
			int idx = 0;
			while (app::MessageReader_get_BytesRemaining(reader, nullptr) >= 4) {
				int selection = app::MessageReader_ReadInt32(reader, nullptr);
				if ((idx >= 76 && idx <= 79) || (idx >= 93 && idx <= 96) || (idx >= 166 && idx <= 169)) {
					STREAM_DEBUG("TOH: SyncCustomSettings[" << idx << "=" << selection);
				}
				idx++;
			}
		}
		break;
		case SetExecutionerTarget:
		{
			Game::PlayerId ExecutionerId = app::MessageReader_ReadByte(reader, nullptr);
			Game::PlayerId TargetId = app::MessageReader_ReadByte(reader, nullptr);
			STREAM_DEBUG("TOH: SetExecutionerTarget:" << ToString(ExecutionerId) << ", TargetId:" << ToString(TargetId));
		}
		break;
		case RemoveExecutionerTarget:
		{
			Game::PlayerId ExecutionerId = app::MessageReader_ReadByte(reader, nullptr);
			STREAM_DEBUG("TOH: RemoveExecutionerTarget:" << ToString(ExecutionerId));
		}
		break;
		case SetBountyTarget:
		{
			Game::PlayerId bountyId = app::MessageReader_ReadByte(reader, nullptr);
			Game::PlayerId targetId = app::MessageReader_ReadByte(reader, nullptr);
			STREAM_DEBUG("TOH: SetBountyTarget:" << ToString(bountyId) << ", TargetId:" << ToString(targetId));
		}
		break;
		case DoSpell:
		{
			Game::PlayerId TargetId = app::MessageReader_ReadByte(reader, nullptr);
			STREAM_DEBUG("TOH: DoSpell:" << ToString(TargetId));
		}
		break;
		default:
			if (callId > 60)
				STREAM_DEBUG("Unknown RPC:" << (int)callId);
			break;
		}
	}
}

// v3.0.2.3
namespace TOH_Y {
	enum CustomRPC
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
		// begin of TOH_Y
		SetHunterShotLimit,
		SetMadSheriffShotLimit,
		SetApprenticeSheriffShotLimit,
		SetDarkHiderKillCount,
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
		Evilneko,//TOH_Y01_11
		AntiAdminer,//TOH_Y01_12
		CursedWolf,//TOH_Y
		NormalImpostor,
		//Madmate
		MadGuardian,
		Madmate,
		MadSnitch,
		MadDictator,//TOH_Y01_9
		MadNatureCalls,//TOH_Y01_10
		MadBrackOuter,
		MadSheriff,
		SKMadmate,
		MSchrodingerCat,//インポスター陣営のシュレディンガーの猫
		//両陣営
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
		Bakery,//TOH_Y01_1
		Hunter,
		TaskManager,
		Nekomata,
		Express,
		Chairman,
		SeeingOff,
		Rainbow,//TOH_Y01_8
		SillySheriff,//TOH_Y
		Sympathizer,//TOH_Y
		CSchrodingerCat,//クルー陣営のシュレディンガーの猫
		//Neutral
		Arsonist,
		Egoist,
		EgoSchrodingerCat,//エゴイスト陣営のシュレディンガーの猫
		Jester,
		Opportunist,
		SchrodingerCat,//第三陣営のシュレディンガーの猫
		Terrorist,
		Executioner,
		Jackal,
		AntiComplete,//TOH_Y01_13
		Workaholic,//TOH_Y01_14
		DarkHide,//TOH_Y
		LoveCutter,//TOH_Y
		JSchrodingerCat,//ジャッカル陣営のシュレディンガーの猫
		OSchrodingerCat,//オポチュニスト陣営のシュレディンガーの猫
		DSchrodingerCat,//ダークキラー陣営のシュレディンガーの猫
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

		Companion,//TOH_Y01
		win,
		WTaskFinish,

		etc = -1
	};

	bool IsImpostor(CustomRoles role) {
		return role >= CustomRoles::Impostor && role <= CustomRoles::NormalImpostor;
	}

	bool IsMadmate(CustomRoles role) {
		return role >= CustomRoles::MadGuardian && role <= CustomRoles::MSchrodingerCat;
	}

	bool IsImpostorTeam(CustomRoles role) {
		return IsImpostor(role) || IsMadmate(role);
	}

	bool IsNeutral(CustomRoles role) {
		return role >= CustomRoles::Arsonist && role <= CustomRoles::HASTroll;
	}

	bool IsCrewmate(CustomRoles role) {
		return !IsImpostorTeam(role) && !IsNeutral(role);
	}

	std::string GetRoleName(CustomRoles role) {
		switch (role) {
		case BountyHunter:
			return "赏金猎人";
		case EvilWatcher:
			return "邪恶的窥视者";
		case FireWorks:
			return "烟花商人";
		case Mafia:
			return "黑手党";
		case SerialKiller:
			return "嗜血杀手";
		case Sniper:
			return "狙击手";
		case Vampire:
			return "吸血鬼";
		case Witch:
			return "女巫";
		case Warlock:
			return "术士";
		case Mare:
			return "梦魇";
		case Puppeteer:
			return "傀儡师";
		case TimeThief:
			return "蚀时者";
		case EvilTracker:
			return "邪恶的追踪者";
		case MadGuardian:
			return "背叛的守卫";
		case Madmate:
			return "叛徒";
		case MadSnitch:
			return "背叛的告密者";
		case SKMadmate:
			return "叛徒小弟";
		case MSchrodingerCat:
		case CSchrodingerCat:
		case EgoSchrodingerCat:
		case SchrodingerCat:
		case JSchrodingerCat:
			return "薛定谔的猫";
		case Watcher:
			return "窥视者";
		case Bait:
			return "诱饵";
		case Lighter:
			return "执灯人";
		case Mayor:
			return "市长";
		case NiceWatcher:
			return "正义的窥视者";
		case SabotageMaster:
			return "修理大师";
		case Sheriff:
			return "警长";
		case Snitch:
			return "告密者";
		case SpeedBooster:
			return "增速者";
		case Trapper:
			return "陷阱师";
		case Dictator:
			return "独裁者";
		case Doctor:
			return "医生";
		case Seer:
			return "灵媒";
		case Arsonist:
			return "纵火犯";
		case Egoist:
			return "野心家";
		case Jester:
			return "小丑";
		case Opportunist:
			return "投机者";
		case Terrorist:
			return "恐怖分子";
		case Executioner:
			return "处刑人";
		case Jackal:
			return "豺狼";
		case HASFox:
			return "狐狸";
		case HASTroll:
			return "猎人";
		case GM:
			return "GM管理员";
		case Lovers:
			return "恋人";
		// TOH_Y
		case Evilneko:
			return "双尾妖猫";
		case AntiAdminer:
			return "反管理人";
		case CursedWolf:
			return "呪狼";
		case NormalImpostor:
			return "普通内鬼";

		case MadDictator:
			return "背叛的独裁者";
		case MadNatureCalls:
			return "背叛的自然呼声";
		case MadBrackOuter:
			return "背叛的控灯人";
		case MadSheriff:
			return "背叛的警长";

		case Bakery:
			return "面包店";
		case Hunter:
			return "猎人";
		case TaskManager:
			return "任务管理器";
		case Nekomata:
			return "双尾怪猫";
		case Express:
			return "邮递员";
		case Chairman:
			return "总裁";
		case SeeingOff:
			return "送行者";
		case Rainbow:
			return "彩虹";
		case SillySheriff:
			return "憨批警长";
		case Sympathizer:
			return "共鳴者";

		case AntiComplete:
			return "防成者";
		case Workaholic:
			return "工作狂";
		case DarkHide:
			return "闇黑者";
		case LoveCutter:
			return "LoveCutter";
		default:
			return std::format("{}", (int32_t)role);
		}
	}

	std::string GetDeathReason(DeathReason reason) {
		switch (reason) {
		case DeathReason::Companion:
			return "同归于尽";
		case DeathReason::win:
			return "猜着";
		case DeathReason::WTaskFinish:
			return "任务完成";
		default:
			return TOH::GetDeathReason((TOH::DeathReason)reason);
		}
	}

	static void HandleRpc(PlayerControl* sender, uint8_t callId, MessageReader* reader) {
		if (!IsHost(sender))
			return; // ignore
		switch ((CustomRPC)callId) {
		case SetHunterShotLimit:
		{
			Game::PlayerId HunterId = app::MessageReader_ReadByte(reader, nullptr);
			float Limit = app::MessageReader_ReadSingle(reader, nullptr);
			STREAM_DEBUG("TOH_Y: SetHunterShotLimit:" << ToString(HunterId) << ", Limit:" << Limit);
		}
		break;
		case SetMadSheriffShotLimit:
		{
			Game::PlayerId SheriffId = app::MessageReader_ReadByte(reader, nullptr);
			float Limit = app::MessageReader_ReadSingle(reader, nullptr);
			STREAM_DEBUG("TOH_Y: SetMadSheriffShotLimit:" << ToString(SheriffId) << ", Limit:" << Limit);
		}
		break;
		case SetApprenticeSheriffShotLimit:
		{
			Game::PlayerId SheriffId = app::MessageReader_ReadByte(reader, nullptr);
			float Limit = app::MessageReader_ReadSingle(reader, nullptr);
			STREAM_DEBUG("TOH_Y: SetApprenticeSheriffShotLimit:" << ToString(SheriffId) << ", Limit:" << Limit);
		}
		break;
		case SetDarkHiderKillCount:
		{
			Game::PlayerId DarkHiderId = app::MessageReader_ReadByte(reader, nullptr);
			bool IsKillerKill = app::MessageReader_ReadBoolean(reader, nullptr);
			STREAM_DEBUG("TOH_Y: SetDarkHiderKillCount:" << ToString(DarkHiderId) << ", IsKillerKill:" << IsKillerKill);
		}
		break;
		case SyncCustomSettings:
		{
			int idx = 0;
			while (app::MessageReader_get_BytesRemaining(reader, nullptr) >= 4) {
				int selection = app::MessageReader_ReadInt32(reader, nullptr);
				//if ((idx >= 76 && idx <= 79) || (idx >= 93 && idx <= 96) || (idx >= 166 && idx <= 169)) {
					STREAM_DEBUG("TOH_Y: SyncCustomSettings[" << idx << "=" << selection);
				//}
				idx++;
			}
		}
		break;
		default:
			TOH::HandleRpc(sender, callId, reader);
			break;
		}
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

	std::string GetRoleName(CustomRoles role) {
		switch (role) {
		case Crewmate:
			return "船员";
		case TOHTOR::BountyHunter:
			return "赏金猎人";
		case TOHTOR::VoteStealer:
			return "窃票者";
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
		case TOHTOR::Vampress:
			return "血族公主";
		case TOHTOR::Witch:
			return "女巫";
		case TOHTOR::Warlock:
			return "术士";
		case TOHTOR::Mare:
			return "梦魇";
		case TOHTOR::Miner:
			return "矿工";
		case TOHTOR::Consort:
			return "邪恶的护卫";
		case TOHTOR::YingYanger:
			return "阴阳师";
		case TOHTOR::Grenadier:
			return "致盲师";
		case TOHTOR::Disperser:
			return "驱散者";
		case TOHTOR::Puppeteer:
			return "傀儡师";
		case TOHTOR::TimeThief:
			return "蚀时者";
		case TOHTOR::Silencer:
			return "沉默者";
		case TOHTOR::Ninja:
			return "忍者";
		case TOHTOR::Swooper:
			return "隐身人";
		case TOHTOR::Camouflager:
			return "伪装师";
		case TOHTOR::Freezer:
			return "冰法师";
		case TOHTOR::Cleaner:
			return "清理工";
		case TOHTOR::EvilGuesser:
			return "邪恶的猜测者";
		case TOHTOR::MadGuardian:
			return "背叛的守卫";
		case TOHTOR::Madmate:
			return "叛徒";
		case TOHTOR::MadSnitch:
			return "背叛的告密者";
		case TOHTOR::CrewPostor:
			return "舰长";
		case TOHTOR::CorruptedSheriff:
			return "背叛的警长";
		case TOHTOR::SKMadmate:
			return "叛徒小弟";
		case TOHTOR::Parasite:
			return "寄居者";
		case TOHTOR::MSchrodingerCat:
		case TOHTOR::CSchrodingerCat:
		case TOHTOR::EgoSchrodingerCat:
		case TOHTOR::SchrodingerCat:
		case TOHTOR::JSchrodingerCat:
			return "薛定谔的猫";
		case TOHTOR::Alturist:
			return "祭师";
		case TOHTOR::Lighter:
			return "执灯人";
		case TOHTOR::Medium:
			return "警探";
		case TOHTOR::Demolitionist:
			return "同命爆手";
		case TOHTOR::Bastion:
			return "埋雷兵";
		case TOHTOR::NiceGuesser:
			return "正义的猜测者";
		case TOHTOR::Escort:
			return "护卫";
		case TOHTOR::Crusader:
			return "十字军";
		case TOHTOR::Psychic:
			return "通灵师";
		case TOHTOR::Mystic:
			return "灵媒";
		case TOHTOR::Swapper:
			return "挑衅者";
		case TOHTOR::Mayor:
			return "市长";
		case TOHTOR::SabotageMaster:
			return "修理大师";
		case TOHTOR::Oracle:
			return "神谕者";
		case TOHTOR::Medic:
			return "医师";
		case TOHTOR::Bodyguard:
			return "保镖";
		case TOHTOR::Sheriff:
			return "警长";
		case TOHTOR::Investigator:
			return "调查员";
		case TOHTOR::Snitch:
			return "告密者";
		case TOHTOR::Transporter:
			return "传送师";
		case TOHTOR::SpeedBooster:
			return "增速者";
		case TOHTOR::Trapper:
			return "陷阱师";
		case TOHTOR::Dictator:
			return "独裁者";
		case TOHTOR::Doctor:
			return "医生";
		case TOHTOR::Child:
			return "小孩";
		case TOHTOR::Veteran:
			return "老兵";
		case TOHTOR::Arsonist:
			return "纵火犯";
		case TOHTOR::Egoist:
			return "野心家";
		case TOHTOR::PlagueBearer:
			return "疫医";
		case TOHTOR::Pestilence:
			return "瘟神";
		case TOHTOR::Vulture:
			return "秃鹫";
		case TOHTOR::TheGlitch:
			return "混沌";
		case TOHTOR::Postman:
			return "邮递员";
		case TOHTOR::Werewolf:
			return "狼人";
		case TOHTOR::NeutWitch:
			return "巫女";
		case TOHTOR::Marksman:
			return "神射手";
		case TOHTOR::GuardianAngelTOU:
			return "守护天使";
		case TOHTOR::Jester:
			return "小丑";
		case TOHTOR::Amnesiac:
			return "窃忆者";
		case TOHTOR::Hacker:
			return "黑客";
		case TOHTOR::PoisonMaster:
			return "制毒师";
		case TOHTOR::BloodKnight:
			return "嗜血骑士";
		case TOHTOR::Hitman:
			return "雇佣杀手";
		case TOHTOR::Phantom:
			return "幻影";
		case TOHTOR::Pirate:
			return "海盗";
		case TOHTOR::Juggernaut:
			return "欲望杀手";
		case TOHTOR::Opportunist:
			return "投机者";
		case TOHTOR::Survivor:
			return "求生者";
		case TOHTOR::Terrorist:
			return "恐怖分子";
		case TOHTOR::Executioner:
			return "处刑人";
		case TOHTOR::Jackal:
			return "豺狼";
		case TOHTOR::Sidekick:
			return "跟班";
		case TOHTOR::HASFox:
			return "狐狸";
		case TOHTOR::HASTroll:
			return "猎人";
		case TOHTOR::Coven:
			return "巫师";
		case TOHTOR::Poisoner:
			return "毒师";
		case TOHTOR::CovenWitch:
			return "巫师团领袖";
		case TOHTOR::HexMaster:
			return "魔法师";
		case TOHTOR::PotionMaster:
			return "药剂师";
		case TOHTOR::Medusa:
			return "美杜莎";
		case TOHTOR::Mimic:
			return "模仿师";
		case TOHTOR::Necromancer:
			return "亡灵法师";
		case TOHTOR::Conjuror:
			return "魔术师";
		case TOHTOR::Painter:
			return "喷漆工";
		case TOHTOR::Janitor:
			return "清洁工";
		case TOHTOR::Supporter:
			return "工人";
		case TOHTOR::LoversWin:
		case TOHTOR::Lovers:
		case TOHTOR::LoversRecode:
			return "恋人";
		case TOHTOR::Flash:
			return "闪电侠";
		case TOHTOR::Escalation:
			return "恐惧者";
		case TOHTOR::TieBreaker:
			return "破局者";
		case TOHTOR::Oblivious:
			return "胆小鬼";
		case TOHTOR::Sleuth:
			return "侦探";
		case TOHTOR::Watcher:
			return "窥视者";
		case TOHTOR::Obvious:
			return "广播员";
		case TOHTOR::Bewilder:
			return "迷幻者";
		case TOHTOR::Bait:
			return "诱饵";
		case TOHTOR::Torch:
			return "火炬手";
		case TOHTOR::Diseased:
			return "患者";
		default:
			return std::format("{}", (int32_t)role);
		}
	}

	std::string GetDeathReason(DeathReason reason) {
		switch (reason) {
		case DeathReason::Kill:
			return "被杀";
		case DeathReason::Vote:
			return "放逐";
		case DeathReason::Suicide:
			return "自杀";
		case DeathReason::Spell:
			return "咒杀";
		case DeathReason::LoversSuicide:
			return "失爱";
		case DeathReason::Bite:
			return "吸血";
		case DeathReason::Bombed:
			return "炸死";
		case DeathReason::Misfire:
			return "走火";
		case DeathReason::Torched:
			return "烧死";
		case DeathReason::Sniped:
			return "狙杀";
		case DeathReason::Execution:
			return "处刑";
		case DeathReason::Disconnected:
			return "断连";
		case DeathReason::Fell:
			return "摔死";
		case DeathReason::Alive:
			return "存活";
		case DeathReason::EarDamage:
			return "耳鸣";
		case DeathReason::Screamed:
			return "惊吓";
		case DeathReason::etc:
			return "其他";
		default:
			return std::format("{}", (int32_t)reason);
		}
	}

	void HandleRpc(PlayerControl* sender, uint8_t callId, MessageReader* reader) {
		if (!IsHost(sender))
			return; // ignore
		switch ((CustomRPC)callId) {
		case SetLoversPlayers:
		{
			auto count = app::MessageReader_ReadInt32(reader, nullptr);
			STREAM_DEBUG("TOHTOR: Lovers Count:" << count);
			while (count-- > 0) {
				Game::PlayerId id = app::MessageReader_ReadByte(reader, nullptr);
				STREAM_DEBUG("TOHTOR:  Lover:" << ToString(id));
			}
		}
		break;
		case SetCustomRole:
		{
			Game::PlayerId id = app::MessageReader_ReadByte(reader, nullptr);
			CustomRoles role = (CustomRoles)app::MessageReader_ReadPackedInt32(reader, nullptr);
			STREAM_DEBUG("TOHTOR: SetCustomRole:" << ToString(id) << ", Role:" << GetRoleName(role)
						 << ", " << (IsImpostorTeam(role) ? "ImpostorTeam" :
									 IsNeutral(role) ? "Neutral" :
									 IsCoven(role) ? "Coven" : "Crewmate"));
			if (role < NoSubRoleAssigned)
				State.assignedModRoles[id].first = (int32_t)role;
			else
				State.assignedModRoles[id].second = (int32_t)role;
		}
		break;
		case SendFireWorksState:
		{
			Game::PlayerId id = app::MessageReader_ReadByte(reader, nullptr);
			int state = app::MessageReader_ReadInt32(reader, nullptr);
			STREAM_DEBUG("TOHTOR: SendFireWorksState:" << ToString(id) << ", FireWorks:" << state);
		}
		break;
		case SniperSync:
		{
			Game::PlayerId id = app::MessageReader_ReadByte(reader, nullptr);
			Game::PlayerId target = app::MessageReader_ReadByte(reader, nullptr);
			STREAM_DEBUG("TOHTOR: SniperSync:" << ToString(id)
						 << ", Target:" << ToString(target));
			bool isNotify = app::MessageReader_ReadBoolean(reader, nullptr);
			if (isNotify) {
				int count = app::MessageReader_ReadInt32(reader, nullptr);
				while (count-- > 0) {
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
		case SetDeathReason:
		{
			Game::PlayerId id = app::MessageReader_ReadByte(reader, nullptr);
			DeathReason deathReason = (DeathReason)app::MessageReader_ReadInt32(reader, nullptr);
			STREAM_DEBUG("TOHTOR: SetDeathReason:" << ToString(id) << ", Reason:" << GetDeathReason(deathReason));
		}
		break;
		case SetDousedPlayer:
		{
			Game::PlayerId id = app::MessageReader_ReadByte(reader, nullptr);
			Game::PlayerId target = app::MessageReader_ReadByte(reader, nullptr);
			bool doused = app::MessageReader_ReadBoolean(reader, nullptr);
			STREAM_DEBUG("TOHTOR: SetDousedPlayer:" << ToString(id)
						 << ", Target:" << ToString(target)
						 << ", Doused:" << doused);
		}
		break;
		case SetCurrentDousingTarget:
		{
			Game::PlayerId id = app::MessageReader_ReadByte(reader, nullptr);
			Game::PlayerId target = app::MessageReader_ReadByte(reader, nullptr);
			STREAM_DEBUG("TOHTOR: SetCurrentDousingTarget:" << ToString(id) << ", Target:" << ToString(target));
		}
		break;
		case SetSheriffShotLimit:
		{
			Game::PlayerId SheriffId = app::MessageReader_ReadByte(reader, nullptr);
			float Limit = app::MessageReader_ReadSingle(reader, nullptr);
			STREAM_DEBUG("TOHTOR: SetSheriffShotLimit:" << ToString(SheriffId) << ", Limit:" << Limit);
		}
		break;
		case SyncCustomSettings:
		{
			int idx = 0;
			while (app::MessageReader_get_BytesRemaining(reader, nullptr) >= 4) {
				int selection = app::MessageReader_ReadInt32(reader, nullptr);
				if (idx == 169) {
					STREAM_DEBUG("TOHTOR: SyncCustomSettings[" << idx << "=" << selection);
				}
				idx++;
			}
		}
		break;
		case SetExecutionerTarget:
		{
			Game::PlayerId ExecutionerId = app::MessageReader_ReadByte(reader, nullptr);
			Game::PlayerId TargetId = app::MessageReader_ReadByte(reader, nullptr);
			STREAM_DEBUG("TOHTOR: SetExecutionerTarget:" << ToString(ExecutionerId) << ", TargetId:" << ToString(TargetId));
		}
		break;
		case RemoveExecutionerTarget:
		{
			Game::PlayerId ExecutionerId = app::MessageReader_ReadByte(reader, nullptr);
			STREAM_DEBUG("TOHTOR: RemoveExecutionerTarget:" << ToString(ExecutionerId));
		}
		break;
		case SetBountyTarget:
		{
			Game::PlayerId bountyId = app::MessageReader_ReadByte(reader, nullptr);
			Game::PlayerId targetId = app::MessageReader_ReadByte(reader, nullptr);
			STREAM_DEBUG("TOHTOR: SetBountyTarget:" << ToString(bountyId) << ", TargetId:" << ToString(targetId));
		}
		break;
		case DoSpell:
		{
			Game::PlayerId TargetId = app::MessageReader_ReadByte(reader, nullptr);
			STREAM_DEBUG("TOHTOR: DoSpell:" << ToString(TargetId));
		}
		break;
		default:
			if (callId > 60)
				STREAM_DEBUG("Unknown RPC:" << (int)callId);
			break;
		}
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
	else if (State.isTOH_Y) {
		TOH_Y::CustomRoles role = (TOH_Y::CustomRoles)State.assignedModRoles[info->fields.PlayerId].first;
		if (TOH_Y::IsImpostorTeam(role)) {
			return Palette__TypeInfo->static_fields->ImpostorRed;
		}
		else if (TOH_Y::IsNeutral(role)) {
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
		if (role2)
			return TOH::GetRoleName(role) + "+" + TOH::GetRoleName(role2);
		else
			return TOH::GetRoleName(role);
	}
	else if (State.isTOH_Y) {
		//if ((*Game::pLocalPlayer)->fields.PlayerId == info->fields.PlayerId)
		//	return "";
		const auto& p = State.assignedModRoles[info->fields.PlayerId];
		TOH_Y::CustomRoles role = (TOH_Y::CustomRoles)p.first;
		TOH_Y::CustomRoles role2 = (TOH_Y::CustomRoles)p.second;
		if (role2)
			return TOH_Y::GetRoleName(role) + "+" + TOH_Y::GetRoleName(role2);
		else
			return TOH_Y::GetRoleName(role);
	}
	else if (State.isTOH_TOR) {
		//if ((*Game::pLocalPlayer)->fields.PlayerId == info->fields.PlayerId)
		//	return "";
		const auto& p = State.assignedModRoles[info->fields.PlayerId];
		TOHTOR::CustomRoles role = (TOHTOR::CustomRoles)p.first;
		TOHTOR::CustomRoles role2 = (TOHTOR::CustomRoles)p.second;
		if (role2)
			return TOHTOR::GetRoleName(role) + "+" + TOHTOR::GetRoleName(role2);
		else
			return TOHTOR::GetRoleName(role);
	}
	else {
		return GetRoleName(info->fields.Role, abbreviated);
	}
}

void HandleRpc(PlayerControl* sender, uint8_t callId, MessageReader* reader) {
	LOG_ASSERT(sender != nullptr);
	if (State.isTOH) {
		return TOH::HandleRpc(sender, callId, reader);
	}
	else if (State.isTOH_Y) {
		return TOH_Y::HandleRpc(sender, callId, reader);
	}
	else if (State.isTOH_TOR) {
		return TOHTOR::HandleRpc(sender, callId, reader);
	}
	else if (callId == 60) { // TOH or TOH:TOR VersionCheck
		if (!IsHost(sender))
			return; // ignore
		auto pVersion = app::MessageReader_ReadString(reader, nullptr);
		app::Version* ver = app::Version_Parse(pVersion, nullptr);
		if (!ver) return;

		std::ostringstream ss;
		ss << "MOD Version:" << convert_from_string(pVersion);
		ss << ", Tag:" << convert_from_string(app::MessageReader_ReadString(reader, nullptr));
		if (ver->fields._Major >= 3) {
			// only for TOH v3.0.0+
			try {
				const auto& modForkId = convert_from_string(app::MessageReader_ReadString(reader, nullptr));
				if (modForkId == "OriginalTOH")
					State.isTOH = true;
				else if (modForkId == "TOH_Y")
					State.isTOH_Y = true;
				else
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
		State.moddedHost = sender->fields.PlayerId;
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