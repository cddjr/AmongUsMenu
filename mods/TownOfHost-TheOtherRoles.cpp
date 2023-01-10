#include "pch-il2cpp.h"
#include <map>
#include <set>
#include <bitset>
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

			COUNT
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
	namespace v0935 {
		enum class CustomRoles {
			//Default
			Crewmate = 0,
			//Impostor(Vanilla)
			Impostor,
			Shapeshifter,
			CrewmateGhost,
			ImpostorGhost,
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
			// EVENT WINNING ROLES
			IdentityTheft,
			Manipulator,
			//    AgiTater,
			Bomber,
			// JK NOW //
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
			// SPECIAL ROLES //
			Cultist,
			Whisperer,
			Chameleon,
			GodFather,
			Mafioso,
			Framer,
			Disguiser,
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
			Terrorist,
			Executioner,
			Jackal,
			AgiTater,
			Sidekick,
			// ALL CAT ROLES //
			SchrodingerCat,
			JSchrodingerCat,
			CSchrodingerCat,
			MSchrodingerCat,
			EgoSchrodingerCat,
			BKSchrodingerCat,
			CPSchrodingerCat,
			JugSchrodingerCat,
			MMSchrodingerCat,
			PesSchrodingerCat,
			WWSchrodingerCat,
			TGSchrodingerCat,
			//HideAndSeek
			HASFox,
			HASTroll,
			//GM
			GM,
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
			sns9,
			sns10,
			rosecolor,
			// random //
			thetaa,
			eevee,
			serverbooster,
			// SELF //
			minaa,
			ess,
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

			//Gurge44
			gu1,
			gu2,
			gu3,
			gu4,
			gu5,
			gu6,
			gu7,
			gu8,
			gu9,
			gu10,
			//Pineapple man670
			pi1,
			pi2,
			pi3,
			pi4,
			pi5,
			pi6,
			pi7,
			pi8,
			pi9,
			pi10,
			//yoclobo
			yo1,
			yo2,
			yo3,
			yo4,
			yo5,
			yo6,
			yo7,
			yo8,
			yo9,
			yo10,
			//Nicky G
			ni1,
			ni2,
			ni3,
			ni4,
			ni5,
			ni6,
			ni7,
			//Milk
			ml1,
			ml2,
			ml3,
			ml4,
			ml5,
			ml6,
			ml7,
			ml8,
			ml9,
			ml10,
			//Paige
			pg1,
			pg2,
			pg3,
			pg4,
			pg5,
			pg6,
			pg7,
			pg8,
			pg9,
			pg10,
			//ck
			cc1,
			cc2,
			cc3,
			cc4,
			cc5,
			cc6,
			cc7,
			cc8,
			cc9,
			cc10,

			COUNT
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
			  && (_revision == 4 || _revision == 5 || _revision == 6))) {
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
		if (_revision >= 5)
			return ((role >= (int)v0935::CustomRoles::Impostor && role <= (int)v0935::CustomRoles::LastImpostor)
			and (role != (int)v0935::CustomRoles::CrewmateGhost &&
				 role != (int)v0935::CustomRoles::Mechanic &&
				 role != (int)v0935::CustomRoles::Physicist &&
				 role != (int)v0935::CustomRoles::Target)) || role == (int)v0935::CustomRoles::CorruptedSheriff;
		
		return ((role >= (int)v0934::CustomRoles::Impostor && role <= (int)v0934::CustomRoles::LastImpostor)
			and (role != (int)v0934::CustomRoles::Mechanic &&
				 role != (int)v0934::CustomRoles::Physicist &&
				 role != (int)v0934::CustomRoles::Target)) || role == (int)v0934::CustomRoles::CorruptedSheriff;
	}
	bool TOH_TOR::IsMadmate(Game::PlayerId player) const {
		RoleId role = this->_assignedRoles[player];
		if (_revision >= 5)
			return role == (int)v0935::CustomRoles::Madmate
			|| role == (int)v0935::CustomRoles::SKMadmate
			|| role == (int)v0935::CustomRoles::MadGuardian
			|| role == (int)v0935::CustomRoles::MadSnitch
			|| role == (int)v0935::CustomRoles::Parasite
			|| role == (int)v0935::CustomRoles::MSchrodingerCat;

		return role == (int)v0934::CustomRoles::Madmate
			|| role == (int)v0934::CustomRoles::SKMadmate
			|| role == (int)v0934::CustomRoles::MadGuardian
			|| role == (int)v0934::CustomRoles::MadSnitch
			|| role == (int)v0934::CustomRoles::Parasite
			|| role == (int)v0934::CustomRoles::MSchrodingerCat;
	}
	bool TOH_TOR::IsNeutral(Game::PlayerId player) const {
		static std::set<RoleId> v0935 {
			(RoleId)v0935::CustomRoles::Jester, 
			(RoleId)v0935::CustomRoles::Jester,
			(RoleId)v0935::CustomRoles::Vulture,
			(RoleId)v0935::CustomRoles::Opportunist,
			(RoleId)v0935::CustomRoles::Survivor,
			(RoleId)v0935::CustomRoles::SchrodingerCat,
			(RoleId)v0935::CustomRoles::Terrorist,
			(RoleId)v0935::CustomRoles::Executioner,
			(RoleId)v0935::CustomRoles::Arsonist,
			(RoleId)v0935::CustomRoles::Egoist,
			(RoleId)v0935::CustomRoles::AgiTater,
			(RoleId)v0935::CustomRoles::EgoSchrodingerCat,
			(RoleId)v0935::CustomRoles::Hitman,
			(RoleId)v0935::CustomRoles::CrewPostor,
			(RoleId)v0935::CustomRoles::Marksman,
			(RoleId)v0935::CustomRoles::PoisonMaster,
			(RoleId)v0935::CustomRoles::Pirate,
			(RoleId)v0935::CustomRoles::Jackal,
			(RoleId)v0935::CustomRoles::PlagueBearer,
			(RoleId)v0935::CustomRoles::Pestilence,
			(RoleId)v0935::CustomRoles::TheGlitch,
			(RoleId)v0935::CustomRoles::Postman,
			(RoleId)v0935::CustomRoles::Werewolf,
			(RoleId)v0935::CustomRoles::Swapper,
			(RoleId)v0935::CustomRoles::GuardianAngelTOU,
			(RoleId)v0935::CustomRoles::NeutWitch,
			(RoleId)v0935::CustomRoles::Amnesiac,
			(RoleId)v0935::CustomRoles::Juggernaut,
			(RoleId)v0935::CustomRoles::Sidekick,
			(RoleId)v0935::CustomRoles::JSchrodingerCat,
			(RoleId)v0935::CustomRoles::Hacker,
			(RoleId)v0935::CustomRoles::Phantom,
			(RoleId)v0935::CustomRoles::BloodKnight,
			(RoleId)v0935::CustomRoles::HASTroll,
			(RoleId)v0935::CustomRoles::Painter,
			(RoleId)v0935::CustomRoles::HASFox, // CAT
			(RoleId)v0935::CustomRoles::BKSchrodingerCat,
			(RoleId)v0935::CustomRoles::CPSchrodingerCat,
			(RoleId)v0935::CustomRoles::JugSchrodingerCat,
			(RoleId)v0935::CustomRoles::MMSchrodingerCat,
			(RoleId)v0935::CustomRoles::PesSchrodingerCat,
			(RoleId)v0935::CustomRoles::WWSchrodingerCat,
			(RoleId)v0935::CustomRoles::TGSchrodingerCat
		};
		static std::set<RoleId> v0934{
			(RoleId)v0934::CustomRoles::Jester,
			(RoleId)v0934::CustomRoles::Vulture,
			(RoleId)v0934::CustomRoles::Opportunist,
			(RoleId)v0934::CustomRoles::Survivor,
			(RoleId)v0934::CustomRoles::SchrodingerCat,
			(RoleId)v0934::CustomRoles::Terrorist,
			(RoleId)v0934::CustomRoles::Executioner,
			(RoleId)v0934::CustomRoles::Arsonist,
			(RoleId)v0934::CustomRoles::Egoist,
			(RoleId)v0934::CustomRoles::EgoSchrodingerCat,
			(RoleId)v0934::CustomRoles::Hitman,
			(RoleId)v0934::CustomRoles::CrewPostor,
			(RoleId)v0934::CustomRoles::Marksman,
			(RoleId)v0934::CustomRoles::PoisonMaster,
			(RoleId)v0934::CustomRoles::Pirate,
			(RoleId)v0934::CustomRoles::Jackal,
			(RoleId)v0934::CustomRoles::PlagueBearer,
			(RoleId)v0934::CustomRoles::Pestilence,
			(RoleId)v0934::CustomRoles::TheGlitch,
			(RoleId)v0934::CustomRoles::Postman,
			(RoleId)v0934::CustomRoles::Werewolf,
			(RoleId)v0934::CustomRoles::Swapper,
			(RoleId)v0934::CustomRoles::GuardianAngelTOU,
			(RoleId)v0934::CustomRoles::NeutWitch,
			(RoleId)v0934::CustomRoles::Amnesiac,
			(RoleId)v0934::CustomRoles::Juggernaut,
			(RoleId)v0934::CustomRoles::Sidekick,
			(RoleId)v0934::CustomRoles::JSchrodingerCat,
			(RoleId)v0934::CustomRoles::Hacker,
			(RoleId)v0934::CustomRoles::Phantom,
			(RoleId)v0934::CustomRoles::BloodKnight,
			(RoleId)v0934::CustomRoles::HASTroll,
			(RoleId)v0934::CustomRoles::Painter,
			(RoleId)v0934::CustomRoles::HASFox
		};
		RoleId role = this->_assignedRoles[player];
		if (_revision >= 5)
			return v0935.contains(role);
		return v0934.contains(role);
	}
	bool TOH_TOR::IsCoven(Game::PlayerId player) const {
		RoleId role = this->_assignedRoles[player];
		if (_revision >= 5)
			return role >= (int)v0935::CustomRoles::Coven && role <= (int)v0935::CustomRoles::Conjuror;
		return role >= (int)v0934::CustomRoles::Coven && role <= (int)v0934::CustomRoles::Conjuror;
	}
	bool TOH_TOR::IsCrewmate(Game::PlayerId player) const {
		return __super::IsCrewmate(player) && !IsCoven(player);
	}
	bool TOH_TOR::IsImpostorTeam(Game::PlayerId player) const {
		if (_revision >= 5)
			return __super::IsImpostorTeam(player) || _assignedRoles[player] == (int)v0935::CustomRoles::CrewPostor;
		return __super::IsImpostorTeam(player) || _assignedRoles[player] == (int)v0934::CustomRoles::CrewPostor;
	}
	std::string TOH_TOR::_GetRoleName(RoleId role) const {
		if (_revision >= 5)
			switch (role) {
			case (int)v0935::CustomRoles::Morphling:
				return "变形者";
			case (int)v0935::CustomRoles::Mechanic:
				return "工程师";
			case (int)v0935::CustomRoles::Physicist:
				return "科学家";
			case (int)v0935::CustomRoles::Target:
				return "Target";
			case (int)v0935::CustomRoles::BountyHunter:
				return "赏金猎人";
			case (int)v0935::CustomRoles::VoteStealer:
				return "窃票者";
			case (int)v0935::CustomRoles::FireWorks:
				return "烟花商人";
			case (int)v0935::CustomRoles::Mafia:
				return "黑手党";
			case (int)v0935::CustomRoles::SerialKiller:
				return "嗜血杀手";
			case (int)v0935::CustomRoles::Sniper:
				return "狙击手";
			case (int)v0935::CustomRoles::Vampire:
				return "吸血鬼";
			case (int)v0935::CustomRoles::Vampress:
				return "血族公主";
			case (int)v0935::CustomRoles::Witch:
				return "女巫";
			case (int)v0935::CustomRoles::Warlock:
				return "术士";
			case (int)v0935::CustomRoles::Mare:
				return "梦魇";
			case (int)v0935::CustomRoles::Miner:
				return "矿工";
			case (int)v0935::CustomRoles::Consort:
				return "邪恶的护卫";
			case (int)v0935::CustomRoles::YingYanger:
				return "阴阳师";
			case (int)v0935::CustomRoles::Grenadier:
				return "致盲师";
			case (int)v0935::CustomRoles::Disperser:
				return "驱散者";
			case (int)v0935::CustomRoles::Puppeteer:
				return "傀儡师";
			case (int)v0935::CustomRoles::TimeThief:
				return "蚀时者";
			case (int)v0935::CustomRoles::Silencer:
				return "沉默者";
			case (int)v0935::CustomRoles::Ninja:
				return "忍者";
			case (int)v0935::CustomRoles::Swooper:
				return "隐身人";
			case (int)v0935::CustomRoles::Camouflager:
				return "伪装师";
			case (int)v0935::CustomRoles::Freezer:
				return "冰法师";
			case (int)v0935::CustomRoles::Cleaner:
				return "清理工";
			case (int)v0935::CustomRoles::EvilGuesser:
				return "邪恶的猜测者";
			case (int)v0935::CustomRoles::MadGuardian:
				return "背叛的守卫";
			case (int)v0935::CustomRoles::Madmate:
				return "叛徒";
			case (int)v0935::CustomRoles::MadSnitch:
				return "背叛的告密者";
			case (int)v0935::CustomRoles::CrewPostor:
				return "舰长";
			case (int)v0935::CustomRoles::CorruptedSheriff:
				return "背叛的警长";
			case (int)v0935::CustomRoles::SKMadmate:
				return "叛徒小弟";
			case (int)v0935::CustomRoles::Parasite:
				return "寄居者";
			case (int)v0935::CustomRoles::MSchrodingerCat:
			case (int)v0935::CustomRoles::CSchrodingerCat:
			case (int)v0935::CustomRoles::EgoSchrodingerCat:
			case (int)v0935::CustomRoles::SchrodingerCat:
			case (int)v0935::CustomRoles::JSchrodingerCat:
				return "薛定谔的猫";
			case (int)v0935::CustomRoles::Alturist:
				return "祭师";
			case (int)v0935::CustomRoles::Lighter:
				return "执灯人";
			case (int)v0935::CustomRoles::Medium:
				return "警探";
			case (int)v0935::CustomRoles::Demolitionist:
				return "同命爆手";
			case (int)v0935::CustomRoles::Bastion:
				return "埋雷兵";
			case (int)v0935::CustomRoles::NiceGuesser:
				return "正义的猜测者";
			case (int)v0935::CustomRoles::Escort:
				return "护卫";
			case (int)v0935::CustomRoles::Crusader:
				return "十字军";
			case (int)v0935::CustomRoles::Psychic:
				return "通灵师";
			case (int)v0935::CustomRoles::Mystic:
				return "灵媒";
			case (int)v0935::CustomRoles::Swapper:
				return "挑衅者";
			case (int)v0935::CustomRoles::Mayor:
				return "市长";
			case (int)v0935::CustomRoles::SabotageMaster:
				return "修理大师";
			case (int)v0935::CustomRoles::Oracle:
				return "神谕者";
			case (int)v0935::CustomRoles::Medic:
				return "医师";
			case (int)v0935::CustomRoles::Bodyguard:
				return "保镖";
			case (int)v0935::CustomRoles::Sheriff:
				return "警长";
			case (int)v0935::CustomRoles::Investigator:
				return "调查员";
			case (int)v0935::CustomRoles::Snitch:
				return "告密者";
			case (int)v0935::CustomRoles::Transporter:
				return "传送师";
			case (int)v0935::CustomRoles::SpeedBooster:
				return "增速者";
			case (int)v0935::CustomRoles::Trapper:
				return "陷阱师";
			case (int)v0935::CustomRoles::Dictator:
				return "独裁者";
			case (int)v0935::CustomRoles::Doctor:
				return "医生";
			case (int)v0935::CustomRoles::Child:
				return "小孩";
			case (int)v0935::CustomRoles::Veteran:
				return "老兵";
			case (int)v0935::CustomRoles::Arsonist:
				return "纵火犯";
			case (int)v0935::CustomRoles::Egoist:
				return "野心家";
			case (int)v0935::CustomRoles::PlagueBearer:
				return "疫医";
			case (int)v0935::CustomRoles::Pestilence:
				return "瘟神";
			case (int)v0935::CustomRoles::Vulture:
				return "秃鹫";
			case (int)v0935::CustomRoles::TheGlitch:
				return "混沌";
			case (int)v0935::CustomRoles::Postman:
				return "邮递员";
			case (int)v0935::CustomRoles::Werewolf:
				return "狼人";
			case (int)v0935::CustomRoles::NeutWitch:
				return "巫女";
			case (int)v0935::CustomRoles::Marksman:
				return "神射手";
			case (int)v0935::CustomRoles::GuardianAngelTOU:
				return "守护天使";
			case (int)v0935::CustomRoles::Jester:
				return "小丑";
			case (int)v0935::CustomRoles::Amnesiac:
				return "窃忆者";
			case (int)v0935::CustomRoles::Hacker:
				return "黑客";
			case (int)v0935::CustomRoles::PoisonMaster:
				return "制毒师";
			case (int)v0935::CustomRoles::BloodKnight:
				return "嗜血骑士";
			case (int)v0935::CustomRoles::Hitman:
				return "雇佣杀手";
			case (int)v0935::CustomRoles::Phantom:
				return "幻影";
			case (int)v0935::CustomRoles::Pirate:
				return "海盗";
			case (int)v0935::CustomRoles::Juggernaut:
				return "欲望杀手";
			case (int)v0935::CustomRoles::Opportunist:
				return "投机者";
			case (int)v0935::CustomRoles::Survivor:
				return "求生者";
			case (int)v0935::CustomRoles::Terrorist:
				return "恐怖分子";
			case (int)v0935::CustomRoles::Executioner:
				return "处刑人";
			case (int)v0935::CustomRoles::Jackal:
				return "豺狼";
			case (int)v0935::CustomRoles::Sidekick:
				return "跟班";
			case (int)v0935::CustomRoles::HASFox:
				return "狐狸";
			case (int)v0935::CustomRoles::HASTroll:
				return "猎人";
			case (int)v0935::CustomRoles::Coven:
				return "巫师";
			case (int)v0935::CustomRoles::Poisoner:
				return "毒师";
			case (int)v0935::CustomRoles::CovenWitch:
				return "巫师团领袖";
			case (int)v0935::CustomRoles::HexMaster:
				return "魔法师";
			case (int)v0935::CustomRoles::PotionMaster:
				return "药剂师";
			case (int)v0935::CustomRoles::Medusa:
				return "美杜莎";
			case (int)v0935::CustomRoles::Mimic:
				return "模仿师";
			case (int)v0935::CustomRoles::Necromancer:
				return "亡灵法师";
			case (int)v0935::CustomRoles::Conjuror:
				return "魔术师";
			case (int)v0935::CustomRoles::Painter:
				return "喷漆工";
			case (int)v0935::CustomRoles::Janitor:
				return "清洁工";
			case (int)v0935::CustomRoles::Supporter:
				return "工人";
			case (int)v0935::CustomRoles::LoversWin:
			case (int)v0935::CustomRoles::Lovers:
			case (int)v0935::CustomRoles::LoversRecode:
				return "恋人";
			case (int)v0935::CustomRoles::Flash:
				return "闪电侠";
			case (int)v0935::CustomRoles::Escalation:
				return "恐惧者";
			case (int)v0935::CustomRoles::TieBreaker:
				return "破局者";
			case (int)v0935::CustomRoles::Oblivious:
				return "胆小鬼";
			case (int)v0935::CustomRoles::Sleuth:
				return "侦探";
			case (int)v0935::CustomRoles::Watcher:
				return "窥视者";
			case (int)v0935::CustomRoles::Obvious:
				return "广播员";
			case (int)v0935::CustomRoles::Bewilder:
				return "迷幻者";
			case (int)v0935::CustomRoles::Bait:
				return "诱饵";
			case (int)v0935::CustomRoles::Torch:
				return "火炬手";
			case (int)v0935::CustomRoles::Diseased:
				return "患者";
				// TODO: and more..
			default:
				if (role == 0 || role == 1 || role == 2 || role == 500)
					return __super::_GetRoleName(role);
				return std::format("{}", role);
			}
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
			if (role == 0 || role == 1 || role == 2 || role == 500)
				return __super::_GetRoleName(role);
			return std::format("{}", role);
		}
	}
	Color TOH_TOR::GetRoleColor(Game::PlayerId player) const {
		static std::map<v0934::CustomRoles, Color> s_roleColors = {
			//バニラ役職
			{ v0934::CustomRoles::Crewmate, ToColor("#ffffff") },
			{ v0934::CustomRoles::Engineer, ToColor("#b6f0ff") },
			{ v0934::CustomRoles::Scientist, ToColor("#b6f0ff") },
			{ v0934::CustomRoles::Mechanic, ToColor("#FFA60A") },
			{ v0934::CustomRoles::Physicist, ToColor("#b6f0ff") },
			{ v0934::CustomRoles::GuardianAngel, ToColor("#ffffff") },
			{ v0934::CustomRoles::Target, ToColor("#000000") },
			{ v0934::CustomRoles::CorruptedSheriff, ToColor("#ff0000") },
			{ v0934::CustomRoles::Watcher, ToColor("#800080") },
			{ v0934::CustomRoles::NiceGuesser, ToColor("#E4E085") },
			{ v0934::CustomRoles::Pirate, ToColor("#EDC240") },
			//特殊クルー役職
			{ v0934::CustomRoles::Bait, ToColor("#00B3B3") },
			{ v0934::CustomRoles::SabotageMaster, ToColor("#0000ff") },
			{ v0934::CustomRoles::Snitch, ToColor("#b8fb4f") },
			{ v0934::CustomRoles::Mayor, ToColor("#204d42") },
			{ v0934::CustomRoles::Sheriff, ToColor("#f8cd46") },
			{ v0934::CustomRoles::Investigator, ToColor("#ffca81") },
			{ v0934::CustomRoles::Lighter, ToColor("#eee5be") },
			//{v0934::CustomRoles::Bodyguard, ToColor("#7FFF00")},
			//{v0934::CustomRoles::Oracle, ToColor("#0042FF")},
			{ v0934::CustomRoles::Bodyguard, ToColor("#5d5d5d") },
			{ v0934::CustomRoles::Oracle, ToColor("#c88dd0") },
			{ v0934::CustomRoles::Medic, ToColor("#006600") },
			{ v0934::CustomRoles::SpeedBooster, ToColor("#00ffff") },
			{ v0934::CustomRoles::Mystic, ToColor("#4D99E6") },
			{ v0934::CustomRoles::Swapper, ToColor("#66E666") },
			{ v0934::CustomRoles::Transporter, ToColor("#00EEFF") },
			{ v0934::CustomRoles::Doctor, ToColor("#80ffdd") },
			{ v0934::CustomRoles::Child, ToColor("#FFFFFF") },
			{ v0934::CustomRoles::Trapper, ToColor("#5a8fd0") },
			{ v0934::CustomRoles::Dictator, ToColor("#df9b00") },
			{ v0934::CustomRoles::Sleuth, ToColor("#803333") },
			{ v0934::CustomRoles::Crusader, ToColor("#c65c39") },
			{ v0934::CustomRoles::Escort, ToColor("#ffb9eb") },
			{ v0934::CustomRoles::PlagueBearer, ToColor("#E6FFB3") },
			{ v0934::CustomRoles::Pestilence, ToColor("#393939") },
			{ v0934::CustomRoles::Vulture, ToColor("#a36727") },
			{ v0934::CustomRoles::CSchrodingerCat, ToColor("#ffffff") }, //シュレディンガーの猫の派生
			{ v0934::CustomRoles::Medium, ToColor("#A680FF") },
			{ v0934::CustomRoles::Alturist, ToColor("#660000") },
			{ v0934::CustomRoles::Psychic, ToColor("#6F698C") },
			//第三陣営役職
			{ v0934::CustomRoles::Arsonist, ToColor("#ff6633") },
			{ v0934::CustomRoles::Jester, ToColor("#ec62a5") },
			{ v0934::CustomRoles::Terrorist, ToColor("#00ff00") },
			{ v0934::CustomRoles::Executioner, ToColor("#C96600") },
			{ v0934::CustomRoles::Opportunist, ToColor("#00ff00") },
			{ v0934::CustomRoles::Survivor, ToColor("#FFE64D") },
			{ v0934::CustomRoles::PoisonMaster, ToColor("#ed2f91") },
			{ v0934::CustomRoles::SchrodingerCat, ToColor("#696969") },
			{ v0934::CustomRoles::Egoist, ToColor("#5600ff") },
			{ v0934::CustomRoles::EgoSchrodingerCat, ToColor("#5600ff") },
			{ v0934::CustomRoles::Jackal, ToColor("#00b4eb") },
			{ v0934::CustomRoles::Sidekick, ToColor("#00b4eb") },
			{ v0934::CustomRoles::Marksman, ToColor("#440101") },
			{ v0934::CustomRoles::Juggernaut, ToColor("#670038") },
			{ v0934::CustomRoles::JSchrodingerCat, ToColor("#00b4eb") },
			{ v0934::CustomRoles::Phantom, ToColor("#662962") },
			{ v0934::CustomRoles::NeutWitch, ToColor("#592e98") },
			{ v0934::CustomRoles::Hitman, ToColor("#ce1924") },
			//HideAndSeek
			{ v0934::CustomRoles::HASFox, ToColor("#e478ff") },
			{ v0934::CustomRoles::BloodKnight, ToColor("#630000") },
			{ v0934::CustomRoles::HASTroll, ToColor("#00ff00") },
			{ v0934::CustomRoles::Painter, ToColor("#FF5733") },
			{ v0934::CustomRoles::Janitor, ToColor("#c67051") },
			{ v0934::CustomRoles::Supporter, ToColor("#00b4eb") },
			// GM
			//サブ役職
			{ v0934::CustomRoles::NoSubRoleAssigned, ToColor("#ffffff") },
			{ v0934::CustomRoles::Lovers, ToColor("#FF66CC") },
			{ v0934::CustomRoles::LoversRecode, ToColor("#FF66CC") },
			{ v0934::CustomRoles::LoversWin, ToColor("#FF66CC") },
			{ v0934::CustomRoles::Flash, ToColor("#FF8080") },
			{ v0934::CustomRoles::Oblivious, ToColor("#808080") },
			{ v0934::CustomRoles::Torch, ToColor("#FFFF99") },
			{ v0934::CustomRoles::Diseased, ToColor("#AAAAAA") },
			{ v0934::CustomRoles::TieBreaker, ToColor("#99E699") },
			{ v0934::CustomRoles::Obvious, ToColor("#D3D3D3") },
			{ v0934::CustomRoles::Escalation, ToColor("#FFB34D") },

			{ v0934::CustomRoles::Coven, ToColor("#bd5dfd") },
			{ v0934::CustomRoles::Veteran, ToColor("#998040") },
			{ v0934::CustomRoles::GuardianAngelTOU, ToColor("#B3FFFF") },
			{ v0934::CustomRoles::TheGlitch, ToColor("#00FF00") },
			{ v0934::CustomRoles::Werewolf, ToColor("#A86629") },
			{ v0934::CustomRoles::Amnesiac, ToColor("#81DDFC") },
			{ v0934::CustomRoles::Bewilder, ToColor("#292644") },
			{ v0934::CustomRoles::Demolitionist, ToColor("#5e2801") },
			{ v0934::CustomRoles::Bastion, ToColor("#524f4d") },
			{ v0934::CustomRoles::Hacker, ToColor("#358013") },
			{ v0934::CustomRoles::CrewPostor, ToColor("#DC6601") },

			// TAGS //
			//TEXT COLORS ROSIE
			{ v0934::CustomRoles::sns1, ToColor("#FFF9DB") },
			{ v0934::CustomRoles::sns2, ToColor("#FCECE0") },
			{ v0934::CustomRoles::sns3, ToColor("#F9DEE5") },
			{ v0934::CustomRoles::sns4, ToColor("#F2C2EE") },
			{ v0934::CustomRoles::sns5, ToColor("#F0ABF1") },
			{ v0934::CustomRoles::sns6, ToColor("#ED93F4") },
			{ v0934::CustomRoles::sns7, ToColor("#EA7BF7") },
			{ v0934::CustomRoles::sns8, ToColor("#E763F9") },
			{ v0934::CustomRoles::rosecolor, ToColor("#FFD6EC") },
			// MISC //
			{ v0934::CustomRoles::eevee, ToColor("#FF8D1C") },
			{ v0934::CustomRoles::serverbooster, ToColor("#f47fff") },
			{ v0934::CustomRoles::thetaa, ToColor("#9A9AEB") },
			// SELF//
			{ v0934::CustomRoles::minaa, ToColor("#C8A2C8") },

			//TEXT COLORS Candy
			{ v0934::CustomRoles::psh1, ToColor("#EF807F") },
			{ v0934::CustomRoles::psh2, ToColor("#F3969C") },
			{ v0934::CustomRoles::psh3, ToColor("#F7ABB8") },
			{ v0934::CustomRoles::psh4, ToColor("#FBC1D5") },
			{ v0934::CustomRoles::psh5, ToColor("#FBC6E9") },
			{ v0934::CustomRoles::psh6, ToColor("#F6B6E0") },
			{ v0934::CustomRoles::psh7, ToColor("#F4AEDC") },
			{ v0934::CustomRoles::psh8, ToColor("#F1A6D7") },
			{ v0934::CustomRoles::psh9, ToColor("#EC96CE") },
		};
		RoleId role = this->_assignedRoles[player];
		auto iter = s_roleColors.find((v0934::CustomRoles)role);
		// TODO: v0935
		if (_revision == 4 && iter != s_roleColors.end())
			return iter->second;
		else if (IsCoven(player))
			return ToColor("#bd5dfd");
		else
			return ModBase::GetRoleColor(player);
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

