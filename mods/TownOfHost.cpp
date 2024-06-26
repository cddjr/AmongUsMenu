#include "pch-il2cpp.h"
#include <map>
#include "TownOfHost.h"
#include "utility.h"
#include "logger.h"

namespace Mods {
	namespace v302 {
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
			etc = -1
		};
	}
	namespace v400 {
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
			NotAssigned = 500,
			LastImpostor,
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
			Revenge,
			Execution,
			Disconnected,
			Fall,
			etc = -1
		};
	}

	TOH::TOH(app::Version* version, std::string_view tag) noexcept(false) {
		SetVersion(version);
		_version = std::format("TOH Version:v{}.{}.{}, tag:{}",
							   _major, _minor, _build,
							   tag);
		LOG_DEBUG(this->GetVersion());
		if (!(_major == 3
			  && _minor == 0
			  && _build == 2)
			&& !(_major == 4
				 && _minor == 0
				 && _build == 0
				 && tag == "52463b13(tags/v4.0.0^0)")
			&& !(_major == 4
				 && _minor == 0
				 && (_build == 1 || _build == 2))) {
			throw std::invalid_argument("Unsupported TOH");
		}
	}

	Mod TOH::GetMod() const {
        return Mod::TownOfHost;
    }

    void TOH::HandleRpc(PlayerControl* sender, uint8_t callId, MessageReader* reader) {
        if (!IsHost(sender))
            return; // ignore
		switch (callId) {
		case (int)v302::CustomRPC::SetCustomRole:
		{
			Game::PlayerId id = app::MessageReader_ReadByte(reader, nullptr);
			RoleId roleId = app::MessageReader_ReadPackedInt32(reader, nullptr);
			if (roleId < 500) {
				this->_assignedRoles[id] = roleId;
			}
			else {
				this->_assignedSubRoles[id] = roleId;
			}
			STREAM_DEBUG("TOH: SetCustomRole:" << ToString(id) << ", Role:" << this->_GetRoleName(roleId));
		}
		break;
		case (int)v302::CustomRPC::SetDeathReason:
		{
			Game::PlayerId id = app::MessageReader_ReadByte(reader, nullptr);
			DeathReasonId reasonId = app::MessageReader_ReadInt32(reader, nullptr);
			this->_deadPlayers[id] = reasonId;
			STREAM_DEBUG("TOH: SetDeathReason:" << ToString(id) << ", Reason:" << this->GetDeathReason(id));
		}
		break;
		case (int)v302::CustomRPC::SetSheriffShotLimit:
		{
			Game::PlayerId SheriffId = app::MessageReader_ReadByte(reader, nullptr);
			float Limit = app::MessageReader_ReadSingle(reader, nullptr);
			STREAM_DEBUG("TOH: SetSheriffShotLimit:" << ToString(SheriffId) << ", Limit:" << Limit);
		}
		break;
		/*
		case (int)v302::CustomRPC::SetLoversPlayers:
		{
			auto count = app::MessageReader_ReadInt32(reader, nullptr);
			STREAM_DEBUG("TOH: Lovers Count:" << count);
			while (count-- > 0) {
				Game::PlayerId id = app::MessageReader_ReadByte(reader, nullptr);
				STREAM_DEBUG("TOH:  Lover:" << ToString(id));
			}
		}
		break;
		case (int)v302::CustomRPC::SyncCustomSettings:
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
		break;*/
		default:
			if (callId > 60)
				STREAM_DEBUG("Unknown RPC:" << (int)callId);
			break;
		}
	}

	bool TOH::IsImpostor(Game::PlayerId player) const {
		RoleId role = this->_assignedRoles[player];
		if (_major >= 4) {
			return role >= (RoleId)v400::CustomRoles::Impostor && role <= (RoleId)v400::CustomRoles::EvilTracker;
		}
		return role >= (RoleId)v302::CustomRoles::Impostor && role <= (RoleId)v302::CustomRoles::LastImpostor;
	}
	bool TOH::IsMadmate(Game::PlayerId player) const {
		RoleId role = this->_assignedRoles[player];
		if (_major >= 4) {
			return role >= (RoleId)v400::CustomRoles::MadGuardian && role <= (RoleId)v400::CustomRoles::MSchrodingerCat;
		}
		return role >= (RoleId)v302::CustomRoles::MadGuardian && role <= (RoleId)v302::CustomRoles::MSchrodingerCat;
	}
	bool TOH::IsNeutral(Game::PlayerId player) const {
		RoleId role = this->_assignedRoles[player];
		if (_major >= 4) {
			return role >= (RoleId)v400::CustomRoles::Arsonist && role <= (RoleId)v400::CustomRoles::HASTroll;
		}
		return role >= (RoleId)v302::CustomRoles::Arsonist && role <= (RoleId)v302::CustomRoles::HASTroll;
	}
	bool TOH::IsCrewmate(Game::PlayerId player) const {
		return !IsImpostorTeam(player) && !IsNeutral(player);
	}
	bool TOH::IsImpostorTeam(Game::PlayerId player) const {
		return IsImpostor(player) || IsMadmate(player);
	}

	std::string TOH::_GetRoleName(RoleId role) const {
		if (role == 0) {
			return "船员";
		}
		else if (role == 1) {
			return "内鬼";
		}
		else if (role == 2) {
			return "变形";
		}
		else if (role == 500) {
			return std::string();
		}
		if (_major >= 4) {
			switch (role) {
			case (int)v400::CustomRoles::BountyHunter:
				return "赏金猎人";
			case (int)v400::CustomRoles::EvilWatcher:
				return "邪恶的窥视者";
			case (int)v400::CustomRoles::FireWorks:
				return "烟花商人";
			case (int)v400::CustomRoles::Mafia:
				return "黑手党";
			case (int)v400::CustomRoles::SerialKiller:
				return "嗜血杀手";
			case (int)v400::CustomRoles::Sniper:
				return "狙击手";
			case (int)v400::CustomRoles::Vampire:
				return "吸血鬼";
			case (int)v400::CustomRoles::Witch:
				return "女巫";
			case (int)v400::CustomRoles::Warlock:
				return "术士";
			case (int)v400::CustomRoles::Mare:
				return "梦魇";
			case (int)v400::CustomRoles::Puppeteer:
				return "傀儡师";
			case (int)v400::CustomRoles::TimeThief:
				return "蚀时者";
			case (int)v400::CustomRoles::EvilTracker:
				return "邪恶的追踪者";
			case (int)v400::CustomRoles::MadGuardian:
				return "背叛的守卫";
			case (int)v400::CustomRoles::Madmate:
				return "叛徒";
			case (int)v400::CustomRoles::MadSnitch:
				return "背叛的告密者";
			case (int)v400::CustomRoles::SKMadmate:
				return "叛徒小弟";
			case (int)v400::CustomRoles::MSchrodingerCat:
			case (int)v400::CustomRoles::CSchrodingerCat:
			case (int)v400::CustomRoles::EgoSchrodingerCat:
			case (int)v400::CustomRoles::SchrodingerCat:
			case (int)v400::CustomRoles::JSchrodingerCat:
				return "薛定谔的猫";
			case (int)v400::CustomRoles::Watcher:
				return "窥视者";
			case (int)v400::CustomRoles::Engineer:
				return "工程师";
			case (int)v400::CustomRoles::GuardianAngel:
				return "天使";
			case (int)v400::CustomRoles::Scientist:
				return "科学家";
			case (int)v400::CustomRoles::Bait:
				return "诱饵";
			case (int)v400::CustomRoles::Lighter:
				return "执灯人";
			case (int)v400::CustomRoles::Mayor:
				return "市长";
			case (int)v400::CustomRoles::NiceWatcher:
				return "正义的窥视者";
			case (int)v400::CustomRoles::SabotageMaster:
				return "修理大师";
			case (int)v400::CustomRoles::Sheriff:
				return "警长";
			case (int)v400::CustomRoles::Snitch:
				return "告密者";
			case (int)v400::CustomRoles::SpeedBooster:
				return "增速者";
			case (int)v400::CustomRoles::Trapper:
				return "陷阱师";
			case (int)v400::CustomRoles::Dictator:
				return "独裁者";
			case (int)v400::CustomRoles::Doctor:
				return "医生";
			case (int)v400::CustomRoles::Seer:
				return "灵媒";
			case (int)v400::CustomRoles::Arsonist:
				return "纵火犯";
			case (int)v400::CustomRoles::Egoist:
				return "野心家";
			case (int)v400::CustomRoles::Jester:
				return "小丑";
			case (int)v400::CustomRoles::Opportunist:
				return "投机者";
			case (int)v400::CustomRoles::Terrorist:
				return "恐怖分子";
			case (int)v400::CustomRoles::Executioner:
				return "处刑人";
			case (int)v400::CustomRoles::Jackal:
				return "豺狼";
			case (int)v400::CustomRoles::HASFox:
				return "狐狸";
			case (int)v400::CustomRoles::HASTroll:
				return "猎人";
			case (int)v400::CustomRoles::GM:
				return "GM管理员";
			case (int)v400::CustomRoles::LastImpostor:
				return "绝境者";
			case (int)v400::CustomRoles::Lovers:
				return "恋人";
			default:
				return std::format("{}", role);
			}
		}
		switch (role) {
		case (int)v302::CustomRoles::BountyHunter:
			return "赏金猎人";
		case (int)v302::CustomRoles::EvilWatcher:
			return "邪恶的窥视者";
		case (int)v302::CustomRoles::FireWorks:
			return "烟花商人";
		case (int)v302::CustomRoles::Mafia:
			return "黑手党";
		case (int)v302::CustomRoles::SerialKiller:
			return "嗜血杀手";
		case (int)v302::CustomRoles::Sniper:
			return "狙击手";
		case (int)v302::CustomRoles::Vampire:
			return "吸血鬼";
		case (int)v302::CustomRoles::Witch:
			return "女巫";
		case (int)v302::CustomRoles::Warlock:
			return "术士";
		case (int)v302::CustomRoles::Mare:
			return "梦魇";
		case (int)v302::CustomRoles::Puppeteer:
			return "傀儡师";
		case (int)v302::CustomRoles::TimeThief:
			return "蚀时者";
		case (int)v302::CustomRoles::EvilTracker:
			return "邪恶的追踪者";
		case (int)v302::CustomRoles::LastImpostor:
			return "绝境者";
		case (int)v302::CustomRoles::MadGuardian:
			return "背叛的守卫";
		case (int)v302::CustomRoles::Madmate:
			return "叛徒";
		case (int)v302::CustomRoles::MadSnitch:
			return "背叛的告密者";
		case (int)v302::CustomRoles::SKMadmate:
			return "叛徒小弟";
		case (int)v302::CustomRoles::MSchrodingerCat:
		case (int)v302::CustomRoles::CSchrodingerCat:
		case (int)v302::CustomRoles::EgoSchrodingerCat:
		case (int)v302::CustomRoles::SchrodingerCat:
		case (int)v302::CustomRoles::JSchrodingerCat:
			return "薛定谔的猫";
		case (int)v302::CustomRoles::Watcher:
			return "窥视者";
		case (int)v302::CustomRoles::Engineer:
			return "工程师";
		case (int)v302::CustomRoles::GuardianAngel:
			return "天使";
		case (int)v302::CustomRoles::Scientist:
			return "科学家";
		case (int)v302::CustomRoles::Bait:
			return "诱饵";
		case (int)v302::CustomRoles::Lighter:
			return "执灯人";
		case (int)v302::CustomRoles::Mayor:
			return "市长";
		case (int)v302::CustomRoles::NiceWatcher:
			return "正义的窥视者";
		case (int)v302::CustomRoles::SabotageMaster:
			return "修理大师";
		case (int)v302::CustomRoles::Sheriff:
			return "警长";
		case (int)v302::CustomRoles::Snitch:
			return "告密者";
		case (int)v302::CustomRoles::SpeedBooster:
			return "增速者";
		case (int)v302::CustomRoles::Trapper:
			return "机关师";//"陷阱师"
		case (int)v302::CustomRoles::Dictator:
			return "独裁者";
		case (int)v302::CustomRoles::Doctor:
			return "医生";
		case (int)v302::CustomRoles::Seer:
			return "灵媒";
		case (int)v302::CustomRoles::Arsonist:
			return "纵火犯";
		case (int)v302::CustomRoles::Egoist:
			return "野心家";
		case (int)v302::CustomRoles::Jester:
			return "小丑";
		case (int)v302::CustomRoles::Opportunist:
			return "投机者";
		case (int)v302::CustomRoles::Terrorist:
			return "恐怖分子";
		case (int)v302::CustomRoles::Executioner:
			return "处刑人";
		case (int)v302::CustomRoles::Jackal:
			return "豺狼";
		case (int)v302::CustomRoles::HASFox:
			return "狐狸";
		case (int)v302::CustomRoles::HASTroll:
			return "猎人";
		case (int)v302::CustomRoles::GM:
			return "GM管理员";
		case (int)v302::CustomRoles::Lovers:
			return "恋人";
		default:
			return std::format("{}", role);
		}
	}

	Color TOH::GetRoleColor(Game::PlayerId player) const {
		static std::map<v400::CustomRoles, Color> s_roleColors = {
			//バニラ役職
			{ v400::CustomRoles::Crewmate, ToColor("#ffffff") },
			{ v400::CustomRoles::Engineer, ToColor("#8cffff") },
			{ v400::CustomRoles::Scientist, ToColor("#8cffff") },
			{ v400::CustomRoles::GuardianAngel, ToColor("#ffffff") },
			//インポスター、シェイプシフター
			//特殊インポスター役職
			//マッドメイト系役職
				//後で追加
			//両陣営可能役職
			{ v400::CustomRoles::Watcher, ToColor("#800080") },
			//特殊クルー役職
			{ v400::CustomRoles::NiceWatcher, ToColor("#800080") }, //ウォッチャーの派生
			{ v400::CustomRoles::Bait, ToColor("#00f7ff") },
			{ v400::CustomRoles::SabotageMaster, ToColor("#0000ff") },
			{ v400::CustomRoles::Snitch, ToColor("#b8fb4f") },
			{ v400::CustomRoles::Mayor, ToColor("#204d42") },
			{ v400::CustomRoles::Sheriff, ToColor("#f8cd46") },
			{ v400::CustomRoles::Lighter, ToColor("#eee5be") },
			{ v400::CustomRoles::SpeedBooster, ToColor("#00ffff") },
			{ v400::CustomRoles::Doctor, ToColor("#80ffdd") },
			{ v400::CustomRoles::Trapper, ToColor("#5a8fd0") },
			{ v400::CustomRoles::Dictator, ToColor("#df9b00") },
			{ v400::CustomRoles::CSchrodingerCat, ToColor("#ffffff") }, //シュレディンガーの猫の派生
			{ v400::CustomRoles::Seer, ToColor("#61b26c") },
			//第三陣営役職
			{ v400::CustomRoles::Arsonist, ToColor("#ff6633") },
			{ v400::CustomRoles::Jester, ToColor("#ec62a5") },
			{ v400::CustomRoles::Terrorist, ToColor("#00ff00") },
			{ v400::CustomRoles::Executioner, ToColor("#611c3a") },
			{ v400::CustomRoles::Opportunist, ToColor("#00ff00") },
			{ v400::CustomRoles::SchrodingerCat, ToColor("#696969") },
			{ v400::CustomRoles::Egoist, ToColor("#5600ff") },
			{ v400::CustomRoles::EgoSchrodingerCat, ToColor("#5600ff") },
			{ v400::CustomRoles::Jackal, ToColor("#00b4eb") },
			{ v400::CustomRoles::JSchrodingerCat, ToColor("#00b4eb") },
			//HideAndSeek
			{ v400::CustomRoles::HASFox, ToColor("#e478ff") },
			{ v400::CustomRoles::HASTroll, ToColor("#00ff00") },
			// GM
			{ v400::CustomRoles::GM, ToColor("#ff5b70") },
			//サブ役職
			{ v400::CustomRoles::LastImpostor, ToColor("#ff0000") },
			{ v400::CustomRoles::Lovers, ToColor("#ff6be4") },

			{ v400::CustomRoles::NotAssigned, ToColor("#ffffff") },
		};

		RoleId role = this->_assignedRoles[player];
		auto iter = s_roleColors.find((v400::CustomRoles)role);
		if (iter != s_roleColors.end())
			return iter->second;
		else
			return ModBase::GetRoleColor(player);
	}
	std::string TOH::GetDeathReason(Game::PlayerId player) const {
		DeathReasonId reason = this->_deadPlayers[player];
		if (_major >= 4) {
			switch (reason) {
			case (int)v400::DeathReason::Kill:
				return "被杀";
			case (int)v400::DeathReason::Vote:
				return "放逐";
			case (int)v400::DeathReason::Suicide:
				return "自杀";
			case (int)v400::DeathReason::Spell:
				return "咒杀";
			case (int)v400::DeathReason::FollowingSuicide:
				return "为爱而死";
			case (int)v400::DeathReason::Bite:
				return "吸血";
			case (int)v400::DeathReason::Bombed:
				return "炸死";
			case (int)v400::DeathReason::Misfire:
				return "走火";
			case (int)v400::DeathReason::Torched:
				return "烧死";
			case (int)v400::DeathReason::Sniped:
				return "狙杀";
			case (int)v400::DeathReason::Revenge:
				return "Revenge";
			case (int)v400::DeathReason::Execution:
				return "处刑";
			case (int)v400::DeathReason::Disconnected:
				return "断连";
			case (int)v400::DeathReason::Fall:
				return "摔死";
			case (int)v400::DeathReason::etc:
				return "其他";
			default:
				return std::format("{}", reason);
			}
		}
		switch (reason) {
		case (int)v302::DeathReason::Kill:
			return "被杀";
		case (int)v302::DeathReason::Vote:
			return "放逐";
		case (int)v302::DeathReason::Suicide:
			return "自杀";
		case (int)v302::DeathReason::Spell:
			return "咒杀";
		case (int)v302::DeathReason::FollowingSuicide:
			return "为爱而死";
		case (int)v302::DeathReason::Bite:
			return "吸血";
		case (int)v302::DeathReason::Bombed:
			return "炸死";
		case (int)v302::DeathReason::Misfire:
			return "走火";
		case (int)v302::DeathReason::Torched:
			return "烧死";
		case (int)v302::DeathReason::Sniped:
			return "狙杀";
		case (int)v302::DeathReason::Execution:
			return "处刑";
		case (int)v302::DeathReason::Disconnected:
			return "断连";
		case (int)v302::DeathReason::Fall:
			return "摔死";
		case (int)v302::DeathReason::etc:
			return "其他";
		default:
			return std::format("{}", reason);
		}
	}
}

