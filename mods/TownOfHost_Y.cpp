#include "pch-il2cpp.h"
#include "TownOfHost_Y.h"
#include "utility.h"
#include "logger.h"

namespace Mods {
	namespace v3023 {
		enum class CustomRPC
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
		enum class CustomRoles
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
		enum class DeathReason
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
	}

	TOH_Y::TOH_Y(app::Version* version, std::string_view tag) noexcept(false) {
		SetVersion(version);
		_version = std::format("TOH_Y Version:v{}.{}.{}.{}, tag:{}",
							   _major, _minor, _build, _revision,
							   tag);
		LOG_DEBUG(this->GetVersion());
		if (!(_major == 3
			  && _minor == 0
			  && _build == 2
			  && _revision == 3)) {
			throw std::invalid_argument("Unsupported TOH_Y");
		}
	}

	Mod TOH_Y::GetMod() const {
        return Mod::TownOfHost_Y;
    }

    void TOH_Y::HandleRpc(PlayerControl* sender, uint8_t callId, MessageReader* reader) {
        if (!IsHost(sender))
            return; // ignore
		switch (callId) {
		case (int)v3023::CustomRPC::SetHunterShotLimit:
		{
			Game::PlayerId HunterId = app::MessageReader_ReadByte(reader, nullptr);
			float Limit = app::MessageReader_ReadSingle(reader, nullptr);
			STREAM_DEBUG("TOH_Y: SetHunterShotLimit:" << ToString(HunterId) << ", Limit:" << Limit);
		}
		break;
		case (int)v3023::CustomRPC::SetMadSheriffShotLimit:
		{
			Game::PlayerId SheriffId = app::MessageReader_ReadByte(reader, nullptr);
			float Limit = app::MessageReader_ReadSingle(reader, nullptr);
			STREAM_DEBUG("TOH_Y: SetMadSheriffShotLimit:" << ToString(SheriffId) << ", Limit:" << Limit);
		}
		break;
		case (int)v3023::CustomRPC::SetApprenticeSheriffShotLimit:
		{
			Game::PlayerId SheriffId = app::MessageReader_ReadByte(reader, nullptr);
			float Limit = app::MessageReader_ReadSingle(reader, nullptr);
			STREAM_DEBUG("TOH_Y: SetApprenticeSheriffShotLimit:" << ToString(SheriffId) << ", Limit:" << Limit);
		}
		break;
		case (int)v3023::CustomRPC::SetDarkHiderKillCount:
		{
			Game::PlayerId DarkHiderId = app::MessageReader_ReadByte(reader, nullptr);
			bool IsKillerKill = app::MessageReader_ReadBoolean(reader, nullptr);
			STREAM_DEBUG("TOH_Y: SetDarkHiderKillCount:" << ToString(DarkHiderId) << ", IsKillerKill:" << IsKillerKill);
		}
		break;
		case (int)v3023::CustomRPC::SyncCustomSettings:
		{
			int idx = 0;
			while (app::MessageReader_get_BytesRemaining(reader, nullptr) >= 4) {
				int selection = app::MessageReader_ReadInt32(reader, nullptr);
				//if ((idx >= 76 && idx <= 79) || (idx >= 93 && idx <= 96) || (idx >= 166 && idx <= 169)) {
				STREAM_DEBUG("TOH_Y: SyncCustomSettings[" << idx << "=" << selection);
				//}
				idx++;
				break;
			}
		}
		break;
		default:
			__super::HandleRpc(sender, callId, reader);
		break;
		}
    }

	bool TOH_Y::IsImpostor(Game::PlayerId player) const {
		RoleId role = this->_assignedRoles[player];
		return role >= (int)v3023::CustomRoles::Impostor && role <= (int)v3023::CustomRoles::LastImpostor;
	}
	bool TOH_Y::IsMadmate(Game::PlayerId player) const {
		RoleId role = this->_assignedRoles[player];
		return role >= (int)v3023::CustomRoles::MadGuardian && role <= (int)v3023::CustomRoles::MSchrodingerCat;
	}
	bool TOH_Y::IsNeutral(Game::PlayerId player) const {
		RoleId role = this->_assignedRoles[player];
		return role >= (int)v3023::CustomRoles::Arsonist && role <= (int)v3023::CustomRoles::HASTroll;
	}
	std::string TOH_Y::_GetRoleName(RoleId role) const {
		switch (role) {
		case (int)v3023::CustomRoles::BountyHunter:
			return "赏金猎人";
		case (int)v3023::CustomRoles::EvilWatcher:
			return "邪恶的窥视者";
		case (int)v3023::CustomRoles::FireWorks:
			return "烟花商人";
		case (int)v3023::CustomRoles::Mafia:
			return "黑手党";
		case (int)v3023::CustomRoles::SerialKiller:
			return "嗜血杀手";
		case (int)v3023::CustomRoles::Sniper:
			return "狙击手";
		case (int)v3023::CustomRoles::Vampire:
			return "吸血鬼";
		case (int)v3023::CustomRoles::Witch:
			return "女巫";
		case (int)v3023::CustomRoles::Warlock:
			return "术士";
		case (int)v3023::CustomRoles::Mare:
			return "梦魇";
		case (int)v3023::CustomRoles::Puppeteer:
			return "傀儡师";
		case (int)v3023::CustomRoles::TimeThief:
			return "蚀时者";
		case (int)v3023::CustomRoles::EvilTracker:
			return "邪恶的追踪者";
		case (int)v3023::CustomRoles::MadGuardian:
			return "背叛的守卫";
		case (int)v3023::CustomRoles::Madmate:
			return "叛徒";
		case (int)v3023::CustomRoles::MadSnitch:
			return "背叛的告密者";
		case (int)v3023::CustomRoles::SKMadmate:
			return "叛徒小弟";
		case (int)v3023::CustomRoles::MSchrodingerCat:
		case (int)v3023::CustomRoles::CSchrodingerCat:
		case (int)v3023::CustomRoles::EgoSchrodingerCat:
		case (int)v3023::CustomRoles::SchrodingerCat:
		case (int)v3023::CustomRoles::JSchrodingerCat:
			return "薛定谔的猫";
		case (int)v3023::CustomRoles::Watcher:
			return "窥视者";
		case (int)v3023::CustomRoles::Engineer:
			return "工程师";
		case (int)v3023::CustomRoles::GuardianAngel:
			return "天使";
		case (int)v3023::CustomRoles::Scientist:
			return "科学家";
		case (int)v3023::CustomRoles::Bait:
			return "诱饵";
		case (int)v3023::CustomRoles::Lighter:
			return "执灯人";
		case (int)v3023::CustomRoles::Mayor:
			return "市长";
		case (int)v3023::CustomRoles::NiceWatcher:
			return "正义的窥视者";
		case (int)v3023::CustomRoles::SabotageMaster:
			return "修理大师";
		case (int)v3023::CustomRoles::Sheriff:
			return "警长";
		case (int)v3023::CustomRoles::Snitch:
			return "告密者";
		case (int)v3023::CustomRoles::SpeedBooster:
			return "增速者";
		case (int)v3023::CustomRoles::Trapper:
			return "陷阱师";
		case (int)v3023::CustomRoles::Dictator:
			return "独裁者";
		case (int)v3023::CustomRoles::Doctor:
			return "医生";
		case (int)v3023::CustomRoles::Seer:
			return "灵媒";
		case (int)v3023::CustomRoles::Arsonist:
			return "纵火犯";
		case (int)v3023::CustomRoles::Egoist:
			return "野心家";
		case (int)v3023::CustomRoles::Jester:
			return "小丑";
		case (int)v3023::CustomRoles::Opportunist:
			return "投机者";
		case (int)v3023::CustomRoles::Terrorist:
			return "恐怖分子";
		case (int)v3023::CustomRoles::Executioner:
			return "处刑人";
		case (int)v3023::CustomRoles::Jackal:
			return "豺狼";
		case (int)v3023::CustomRoles::HASFox:
			return "狐狸";
		case (int)v3023::CustomRoles::HASTroll:
			return "猎人";
		case (int)v3023::CustomRoles::GM:
			return "GM管理员";
		case (int)v3023::CustomRoles::Lovers:
			return "恋人";
			// TOH_Y
		case (int)v3023::CustomRoles::Evilneko:
			return "双尾妖猫";
		case (int)v3023::CustomRoles::AntiAdminer:
			return "反管理人";
		case (int)v3023::CustomRoles::CursedWolf:
			return "呪狼";
		case (int)v3023::CustomRoles::NormalImpostor:
			return "普通内鬼";

		case (int)v3023::CustomRoles::MadDictator:
			return "背叛的独裁者";
		case (int)v3023::CustomRoles::MadNatureCalls:
			return "背叛的自然呼声";
		case (int)v3023::CustomRoles::MadBrackOuter:
			return "背叛的控灯人";
		case (int)v3023::CustomRoles::MadSheriff:
			return "背叛的警长";

		case (int)v3023::CustomRoles::Bakery:
			return "面包店";
		case (int)v3023::CustomRoles::Hunter:
			return "猎人";
		case (int)v3023::CustomRoles::TaskManager:
			return "任务管理器";
		case (int)v3023::CustomRoles::Nekomata:
			return "双尾怪猫";
		case (int)v3023::CustomRoles::Express:
			return "邮递员";
		case (int)v3023::CustomRoles::Chairman:
			return "总裁";
		case (int)v3023::CustomRoles::SeeingOff:
			return "送行者";
		case (int)v3023::CustomRoles::Rainbow:
			return "彩虹";
		case (int)v3023::CustomRoles::SillySheriff:
			return "憨批警长";
		case (int)v3023::CustomRoles::Sympathizer:
			return "共鳴者";
		case (int)v3023::CustomRoles::AntiComplete:
			return "防成者";
		case (int)v3023::CustomRoles::Workaholic:
			return "工作狂";
		case (int)v3023::CustomRoles::DarkHide:
			return "闇黑者";
		case (int)v3023::CustomRoles::LoveCutter:
			return "LoveCutter";
		default:
			return __super::_GetRoleName(role);
		}
	}
	std::string TOH_Y::GetDeathReason(Game::PlayerId player) const {
		DeathReasonId reason = this->_deadPlayers[player];
		switch (reason) {
		case (int)v3023::DeathReason::Companion:
			return "同归于尽";
		case (int)v3023::DeathReason::win:
			return "猜着";
		case (int)v3023::DeathReason::WTaskFinish:
			return "任务完成";
		default:
			return __super::GetDeathReason(player);
		}
	}
}

