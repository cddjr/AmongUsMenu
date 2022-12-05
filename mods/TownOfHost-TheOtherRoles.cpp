#include "pch-il2cpp.h"
#include "TownOfHost-TheOtherRoles.h"
#include "utility.h"
#include "logger.h"

namespace Mods {
	namespace v0934 {
		enum class CustomRPC
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
		enum class CustomRoles
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
		enum class DeathReason
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
	}

	TOH_TOR::TOH_TOR(app::Version* version, std::string_view tag) noexcept(false) {
		SetVersion(version);
		_version = std::format("TOH:TOR Version:v{}.{}.{}.{}, tag:{}",
							   _major, _minor, _build, _revision,
							   tag);
		LOG_DEBUG(this->GetVersion());
		if (!(_major == 0
			  && _minor == 9
			  && _build == 3
			  && _revision == 4)) {
			throw std::invalid_argument("Unsupported TOH:TOR");
		}
	}

	Mod TOH_TOR::GetMod() const {
        return Mod::TownOfHost_TheOtherRoles;
    }

    void TOH_TOR::HandleRpc(PlayerControl* sender, uint8_t callId, MessageReader* reader) {
        if (!IsHost(sender))
            return; // ignore
		switch (callId) {
		case (int)v0934::CustomRPC::SetSheriffShotLimit:
		{
			Game::PlayerId SheriffId = app::MessageReader_ReadByte(reader, nullptr);
			float Limit = app::MessageReader_ReadSingle(reader, nullptr);
			STREAM_DEBUG("TOHTOR: SetSheriffShotLimit:" << ToString(SheriffId) << ", Limit:" << Limit);
		}
		break;
		default:
		{
			ScopedModVersion ver(3, 0, 2, 0);
			__super::HandleRpc(sender, callId, reader);
		}
		break;
		}
    }

	bool TOH_TOR::IsImpostor(Game::PlayerId player) const {
		RoleId role = this->_assignedRoles[player];
		return (role >= (int)v0934::CustomRoles::Impostor && role <= (int)v0934::CustomRoles::LastImpostor)
			and (role != (int)v0934::CustomRoles::Mechanic &&
				 role != (int)v0934::CustomRoles::Physicist &&
				 role != (int)v0934::CustomRoles::Target);
	}
	bool TOH_TOR::IsMadmate(Game::PlayerId player) const {
		RoleId role = this->_assignedRoles[player];
		return role >= (int)v0934::CustomRoles::MadGuardian && role <= (int)v0934::CustomRoles::MSchrodingerCat;
	}
	bool TOH_TOR::IsNeutral(Game::PlayerId player) const {
		RoleId role = this->_assignedRoles[player];
		return role >= (int)v0934::CustomRoles::Arsonist && role <= (int)v0934::CustomRoles::HASTroll;
	}
	bool TOH_TOR::IsCoven(Game::PlayerId player) const {
		RoleId role = this->_assignedRoles[player];
		return role >= (int)v0934::CustomRoles::Coven && role <= (int)v0934::CustomRoles::Conjuror;
	}
	bool TOH_TOR::IsCrewmate(Game::PlayerId player) const {
		return __super::IsCrewmate(player) && !IsCoven(player);
	}
	bool TOH_TOR::IsImpostorTeam(Game::PlayerId player) const {
		return __super::IsImpostorTeam(player) || _assignedRoles[player] == (int)v0934::CustomRoles::CrewPostor;
	}
	std::string TOH_TOR::_GetRoleName(RoleId role) const {
		switch (role) {
		case (int)v0934::CustomRoles::Morphling:
			return "变形者";
		case (int)v0934::CustomRoles::Mechanic:
			return "工程师";
		case (int)v0934::CustomRoles::Physicist:
			return "科学家";
		case (int)v0934::CustomRoles::Target:
			return "Target";
		case (int)v0934::CustomRoles::BountyHunter:
			return "赏金猎人";
		case (int)v0934::CustomRoles::VoteStealer:
			return "窃票者";
		case (int)v0934::CustomRoles::FireWorks:
			return "烟花商人";
		case (int)v0934::CustomRoles::Mafia:
			return "黑手党";
		case (int)v0934::CustomRoles::SerialKiller:
			return "嗜血杀手";
		case (int)v0934::CustomRoles::Sniper:
			return "狙击手";
		case (int)v0934::CustomRoles::Vampire:
			return "吸血鬼";
		case (int)v0934::CustomRoles::Vampress:
			return "血族公主";
		case (int)v0934::CustomRoles::Witch:
			return "女巫";
		case (int)v0934::CustomRoles::Warlock:
			return "术士";
		case (int)v0934::CustomRoles::Mare:
			return "梦魇";
		case (int)v0934::CustomRoles::Miner:
			return "矿工";
		case (int)v0934::CustomRoles::Consort:
			return "邪恶的护卫";
		case (int)v0934::CustomRoles::YingYanger:
			return "阴阳师";
		case (int)v0934::CustomRoles::Grenadier:
			return "致盲师";
		case (int)v0934::CustomRoles::Disperser:
			return "驱散者";
		case (int)v0934::CustomRoles::Puppeteer:
			return "傀儡师";
		case (int)v0934::CustomRoles::TimeThief:
			return "蚀时者";
		case (int)v0934::CustomRoles::Silencer:
			return "沉默者";
		case (int)v0934::CustomRoles::Ninja:
			return "忍者";
		case (int)v0934::CustomRoles::Swooper:
			return "隐身人";
		case (int)v0934::CustomRoles::Camouflager:
			return "伪装师";
		case (int)v0934::CustomRoles::Freezer:
			return "冰法师";
		case (int)v0934::CustomRoles::Cleaner:
			return "清理工";
		case (int)v0934::CustomRoles::EvilGuesser:
			return "邪恶的猜测者";
		case (int)v0934::CustomRoles::MadGuardian:
			return "背叛的守卫";
		case (int)v0934::CustomRoles::Madmate:
			return "叛徒";
		case (int)v0934::CustomRoles::MadSnitch:
			return "背叛的告密者";
		case (int)v0934::CustomRoles::CrewPostor:
			return "舰长";
		case (int)v0934::CustomRoles::CorruptedSheriff:
			return "背叛的警长";
		case (int)v0934::CustomRoles::SKMadmate:
			return "叛徒小弟";
		case (int)v0934::CustomRoles::Parasite:
			return "寄居者";
		case (int)v0934::CustomRoles::MSchrodingerCat:
		case (int)v0934::CustomRoles::CSchrodingerCat:
		case (int)v0934::CustomRoles::EgoSchrodingerCat:
		case (int)v0934::CustomRoles::SchrodingerCat:
		case (int)v0934::CustomRoles::JSchrodingerCat:
			return "薛定谔的猫";
		case (int)v0934::CustomRoles::Alturist:
			return "祭师";
		case (int)v0934::CustomRoles::Lighter:
			return "执灯人";
		case (int)v0934::CustomRoles::Medium:
			return "警探";
		case (int)v0934::CustomRoles::Demolitionist:
			return "同命爆手";
		case (int)v0934::CustomRoles::Bastion:
			return "埋雷兵";
		case (int)v0934::CustomRoles::NiceGuesser:
			return "正义的猜测者";
		case (int)v0934::CustomRoles::Escort:
			return "护卫";
		case (int)v0934::CustomRoles::Crusader:
			return "十字军";
		case (int)v0934::CustomRoles::Psychic:
			return "通灵师";
		case (int)v0934::CustomRoles::Mystic:
			return "灵媒";
		case (int)v0934::CustomRoles::Swapper:
			return "挑衅者";
		case (int)v0934::CustomRoles::Mayor:
			return "市长";
		case (int)v0934::CustomRoles::SabotageMaster:
			return "修理大师";
		case (int)v0934::CustomRoles::Oracle:
			return "神谕者";
		case (int)v0934::CustomRoles::Medic:
			return "医师";
		case (int)v0934::CustomRoles::Bodyguard:
			return "保镖";
		case (int)v0934::CustomRoles::Sheriff:
			return "警长";
		case (int)v0934::CustomRoles::Investigator:
			return "调查员";
		case (int)v0934::CustomRoles::Snitch:
			return "告密者";
		case (int)v0934::CustomRoles::Transporter:
			return "传送师";
		case (int)v0934::CustomRoles::SpeedBooster:
			return "增速者";
		case (int)v0934::CustomRoles::Trapper:
			return "陷阱师";
		case (int)v0934::CustomRoles::Dictator:
			return "独裁者";
		case (int)v0934::CustomRoles::Doctor:
			return "医生";
		case (int)v0934::CustomRoles::Child:
			return "小孩";
		case (int)v0934::CustomRoles::Veteran:
			return "老兵";
		case (int)v0934::CustomRoles::Arsonist:
			return "纵火犯";
		case (int)v0934::CustomRoles::Egoist:
			return "野心家";
		case (int)v0934::CustomRoles::PlagueBearer:
			return "疫医";
		case (int)v0934::CustomRoles::Pestilence:
			return "瘟神";
		case (int)v0934::CustomRoles::Vulture:
			return "秃鹫";
		case (int)v0934::CustomRoles::TheGlitch:
			return "混沌";
		case (int)v0934::CustomRoles::Postman:
			return "邮递员";
		case (int)v0934::CustomRoles::Werewolf:
			return "狼人";
		case (int)v0934::CustomRoles::NeutWitch:
			return "巫女";
		case (int)v0934::CustomRoles::Marksman:
			return "神射手";
		case (int)v0934::CustomRoles::GuardianAngelTOU:
			return "守护天使";
		case (int)v0934::CustomRoles::Jester:
			return "小丑";
		case (int)v0934::CustomRoles::Amnesiac:
			return "窃忆者";
		case (int)v0934::CustomRoles::Hacker:
			return "黑客";
		case (int)v0934::CustomRoles::PoisonMaster:
			return "制毒师";
		case (int)v0934::CustomRoles::BloodKnight:
			return "嗜血骑士";
		case (int)v0934::CustomRoles::Hitman:
			return "雇佣杀手";
		case (int)v0934::CustomRoles::Phantom:
			return "幻影";
		case (int)v0934::CustomRoles::Pirate:
			return "海盗";
		case (int)v0934::CustomRoles::Juggernaut:
			return "欲望杀手";
		case (int)v0934::CustomRoles::Opportunist:
			return "投机者";
		case (int)v0934::CustomRoles::Survivor:
			return "求生者";
		case (int)v0934::CustomRoles::Terrorist:
			return "恐怖分子";
		case (int)v0934::CustomRoles::Executioner:
			return "处刑人";
		case (int)v0934::CustomRoles::Jackal:
			return "豺狼";
		case (int)v0934::CustomRoles::Sidekick:
			return "跟班";
		case (int)v0934::CustomRoles::HASFox:
			return "狐狸";
		case (int)v0934::CustomRoles::HASTroll:
			return "猎人";
		case (int)v0934::CustomRoles::Coven:
			return "巫师";
		case (int)v0934::CustomRoles::Poisoner:
			return "毒师";
		case (int)v0934::CustomRoles::CovenWitch:
			return "巫师团领袖";
		case (int)v0934::CustomRoles::HexMaster:
			return "魔法师";
		case (int)v0934::CustomRoles::PotionMaster:
			return "药剂师";
		case (int)v0934::CustomRoles::Medusa:
			return "美杜莎";
		case (int)v0934::CustomRoles::Mimic:
			return "模仿师";
		case (int)v0934::CustomRoles::Necromancer:
			return "亡灵法师";
		case (int)v0934::CustomRoles::Conjuror:
			return "魔术师";
		case (int)v0934::CustomRoles::Painter:
			return "喷漆工";
		case (int)v0934::CustomRoles::Janitor:
			return "清洁工";
		case (int)v0934::CustomRoles::Supporter:
			return "工人";
		case (int)v0934::CustomRoles::LoversWin:
		case (int)v0934::CustomRoles::Lovers:
		case (int)v0934::CustomRoles::LoversRecode:
			return "恋人";
		case (int)v0934::CustomRoles::Flash:
			return "闪电侠";
		case (int)v0934::CustomRoles::Escalation:
			return "恐惧者";
		case (int)v0934::CustomRoles::TieBreaker:
			return "破局者";
		case (int)v0934::CustomRoles::Oblivious:
			return "胆小鬼";
		case (int)v0934::CustomRoles::Sleuth:
			return "侦探";
		case (int)v0934::CustomRoles::Watcher:
			return "窥视者";
		case (int)v0934::CustomRoles::Obvious:
			return "广播员";
		case (int)v0934::CustomRoles::Bewilder:
			return "迷幻者";
		case (int)v0934::CustomRoles::Bait:
			return "诱饵";
		case (int)v0934::CustomRoles::Torch:
			return "火炬手";
		case (int)v0934::CustomRoles::Diseased:
			return "患者";
		default:
		{
			//FIXME:
			ScopedModVersion ver(3, 0, 2, 0);
			return __super::_GetRoleName(role);
		}
		}
	}
	Color TOH_TOR::GetRoleColor(Game::PlayerId player) const {
		if (IsCoven(player)) {
			return Palette__TypeInfo->static_fields->Purple;
		}
		else {
			return __super::GetRoleColor(player);
		}
	}
	std::string TOH_TOR::GetDeathReason(Game::PlayerId player) const {
		DeathReasonId reason = this->_deadPlayers[player];
		switch (reason) {
		case (int)v0934::DeathReason::LoversSuicide:
			return "失爱";
		case (int)v0934::DeathReason::Alive:
			return "存活";
		case (int)v0934::DeathReason::EarDamage:
			return "耳鸣";
		case (int)v0934::DeathReason::Screamed:
			return "惊吓";
		default:
		{
			//FIXME:
			ScopedModVersion ver(3, 0, 2, 0);
			return __super::GetDeathReason(player);
		}
		}
	}
}

