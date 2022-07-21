#include "pch-il2cpp.h"
#include "_hooks.h"
#include "utility.h"
#include "state.hpp"
#include "game.h"
#include "logger.h"
#include "utility.h"
#include "replay.hpp"
#include "profiler.h"
#include <sstream>
#include "esp.hpp"

void dInnerNetClient_Update(InnerNetClient* __this, MethodInfo* method)
{

    if (!IsInLobby()) {
        State.LobbyTimer = -1;
    }

    if (IsInLobby() && State.LobbyTimer > 0) {
        State.LobbyTimer--;
    }

    if (!IsInGame() || State.InMeeting) {
        if (State.PlayMedbayScan) {
            State.PlayMedbayScan = false;
            State.rpcQueue.push(new RpcSetScanner(false));
        }
    }

    if ((IsInGame() || IsInLobby()) && State.HotkeyNoClip) {
        if (!(GetPlayerData(*Game::pLocalPlayer)->fields.IsDead)) {
            if (State.NoClip)
                app::GameObject_set_layer(app::Component_get_gameObject((Component_1*)(*Game::pLocalPlayer), NULL), app::LayerMask_NameToLayer(convert_to_string("Ghost"), NULL), NULL);
            else
                app::GameObject_set_layer(app::Component_get_gameObject((Component_1*)(*Game::pLocalPlayer), NULL), app::LayerMask_NameToLayer(convert_to_string("Players"), NULL), NULL);
        }
        State.HotkeyNoClip = false;
    }

    if (!IsInGame()) {

        State.FreeCam = false;
        State.InMeeting = false;
        State.EnableZoom = false;
        State.DisableLights = false;
        State.CloseAllDoors = false;
        State.playerToFollow = PlayerSelection();
        State.FollowerCam = nullptr;

        if (!IsInLobby()) {
            State.selectedPlayer = PlayerSelection();
            State.NoClip = false;
            State.HotkeyNoClip = false;
            State.originalName = "-";
        }
    }
    else {
        if (!State.rpcQueue.empty()) {
            auto rpc = State.rpcQueue.front();
            //Looks like there is a check on Task completion when u are dead.
            //The maximum amount of Tasks that can be completed per Update is at 6.
            auto maxProcessedTasks = 6;
			auto processedTaskCompletes = 0;
			if (dynamic_cast<RpcCompleteTask*>(rpc))
			{
				if (processedTaskCompletes < maxProcessedTasks)
				{
					State.rpcQueue.pop();
					rpc->Process();
					processedTaskCompletes++;
				}
			}
			else
			{
				State.rpcQueue.pop();
				rpc->Process();
			}
            delete rpc;
        }

        if (State.CloseAllDoors) {
            for (auto door : State.mapDoors) {
                State.rpcQueue.push(new RpcCloseDoorsOfType(door, false));
            }
            State.CloseAllDoors = false;
        }

        if (State.MoveInVent && (*Game::pLocalPlayer)->fields.inVent) {
            (*Game::pLocalPlayer)->fields.moveable = true;
        }
    }

    if (IsInLobby()) {
        if (State.originalName == "-") {
            app::GameData_PlayerOutfit* outfit = GetPlayerOutfit(GetPlayerData(*Game::pLocalPlayer));
            if (outfit != NULL)
                State.originalName = convert_from_string(GameData_PlayerOutfit_get_PlayerName(outfit, nullptr));
        }

        if (!State.lobbyRpcQueue.empty()) {
            auto rpc = State.lobbyRpcQueue.front();
            State.lobbyRpcQueue.pop();

            rpc->Process();
            delete rpc;
        }
    }

    static int nameChangeCycleDelay = 0; //If we spam too many name changes, we're banned

    if (nameChangeCycleDelay <= 0 && !State.activeImpersonation) {
        std::string userName;
        synchronized(State.nameMutex) {
            userName = State.userName;
        }
        if ((convert_from_string(app::SaveManager_get_PlayerName(nullptr)) != userName) && !userName.empty()) {
            app::SaveManager_set_PlayerName(convert_to_string(userName), nullptr);
            LOG_INFO("Name mismatch, setting name to \"" + userName + "\"");
            if (IsInGame())
                State.rpcQueue.push(new RpcSetName(userName));
            else if (IsInLobby())
                State.lobbyRpcQueue.push(new RpcSetName(userName));
            nameChangeCycleDelay = 100; //Should be approximately two second
        }
    }
    else {
        nameChangeCycleDelay--;
    }

    InnerNetClient_Update(__this, method);
}

#include <set>
void dVentilationSystem_Deserialize(VentilationSystem* __this, MessageReader* reader, bool initialState, MethodInfo* method) {
    app::VentilationSystem_Deserialize(__this, reader, initialState, method);
    if (auto data = GetPlayerData(*Game::pLocalPlayer); PlayerIsImpostor(data)) {
        return;
    }
    std::set<uint8_t> excludeVentIds;
    std::set<uint8_t> ventIds;
    il2cpp::Dictionary dict = __this->fields.PlayersInsideVents;
    for (const auto& pair : dict) {
        auto player = PlayerSelection(GetPlayerControlById(pair.key)).validate();
        if (!player) continue;
        if (!player.is_LocalPlayer()
            && PlayerIsImpostor(player.get_PlayerData())) {
            ventIds.emplace(pair.value);
        }
        else {
            excludeVentIds.emplace(pair.value);
        }
    }
    for (auto ventId : ventIds) {
        if (excludeVentIds.contains(ventId)
            || GenerateRandomNumber(1, 100) <= 98) {
            //STREAM_DEBUG("ignored Vent " << +ventId);
            continue;
        }
        // 2% chance
        STREAM_DEBUG("BootImpostors Vent " << +ventId);
        // Don't call PlayerPhysics_RpcBootFromVent directly or you will be banned.
        app::VentilationSystem_Update(VentilationSystem_Operation__Enum::BootImpostors, ventId, nullptr);
    }
}

void dAmongUsClient_OnPlayerLeft(AmongUsClient* __this, ClientData* data, DisconnectReasons__Enum reason, MethodInfo* method) {
    if (data->fields.Character) { // Don't use Object_1_IsNotNull().
        auto playerInfo = GetPlayerData(data->fields.Character);
        Log.Debug(ToString(data->fields.Character) + " has left the game.");

        auto it = std::find(State.aumUsers.begin(), State.aumUsers.end(), data->fields.Character->fields.PlayerId);
        if (it != State.aumUsers.end())
            State.aumUsers.erase(it);

        if (auto evtPlayer = GetEventPlayer(playerInfo); evtPlayer) {
            synchronized(Replay::replayEventMutex) {
        	    State.liveReplayEvents.emplace_back(std::make_unique<DisconnectEvent>(evtPlayer.value()));
            }
        }
    }
    else {
        //Found this happens on game ending occasionally
        //Log.Info(std::format("Client {} has left the game.", data->fields.Id));
    }

    AmongUsClient_OnPlayerLeft(__this, data, reason, method);
}

bool bogusTransformSnap(PlayerSelection& _player, Vector2 newPosition)
{
    const auto& player = _player.validate();
    if (!player.has_value())
        Log.Debug("bogusTransformSnap received invalid player!");
    if (!player.has_value()) return false; //Error getting playercontroller
    if (player.is_LocalPlayer()) return false; //We are not going to log ourselves
    if (player.get_PlayerControl()->fields.inVent) return false; //Vent buttons are warps
    if (GameObject_get_layer(app::Component_get_gameObject((Component_1*)player.get_PlayerControl(), NULL), NULL) == LayerMask_NameToLayer(convert_to_string("Ghost"), NULL))
        return false; //For some reason the playercontroller is not marked dead at this point, so we check what layer the player is on
    auto currentPosition = PlayerControl_GetTruePosition(player.get_PlayerControl(), NULL);
    auto distanceToTarget = (int32_t)Vector2_Distance(currentPosition, newPosition, NULL); //rounding off as the smallest kill distance is zero
    auto killDistance = std::clamp((*Game::pGameOptionsData)->fields._.killDistance, 0, 2);
    auto initialSpawnLocation = GetSpawnLocation(player.get_PlayerControl()->fields.PlayerId, (int)il2cpp::List((*Game::pGameData)->fields.AllPlayers).size(), true);
    auto meetingSpawnLocation = GetSpawnLocation(player.get_PlayerControl()->fields.PlayerId, (int)il2cpp::List((*Game::pGameData)->fields.AllPlayers).size(), false);
    if (Equals(initialSpawnLocation, newPosition)) return false;
    if (Equals(meetingSpawnLocation, newPosition)) return false;  //You are warped to your spawn at meetings and start of games
    if (IsAirshipSpawnLocation(newPosition)) return false;
    if (PlayerIsImpostor(player.get_PlayerData()) && distanceToTarget <= killDistance) 
        return false;
    std::ostringstream ss;

    ss << "From " << +currentPosition.x << "," << +currentPosition.y << " to " << +newPosition.x << "," << +newPosition.y << std::endl;
    ss << "Range to target " << +distanceToTarget << ", KillDistance: " << +killDistance << std::endl;
    ss << "Initial Spawn Location " << +initialSpawnLocation.x << "," << +initialSpawnLocation.y << std::endl;
    ss << "Meeting Spawn Location " << +meetingSpawnLocation.x << "," << +meetingSpawnLocation.y << std::endl;
    ss << "-------";
    Log.Debug(ss.str());
    return true; //We have ruled out all possible scenarios.  Off with his head!
}

void dCustomNetworkTransform_SnapTo(CustomNetworkTransform* __this, Vector2 position, uint16_t minSid, MethodInfo* method) {
    //Leave this out until we fix it.
    /*
    if (!IsInGame()) {
        CustomNetworkTransform_SnapTo(__this, position, minSid, method);
        return;
    }

    PlayerSelection player;
    for (auto p : GetAllPlayerControl()) {
        if (p->fields.NetTransform == __this) {
            player = PlayerSelection(p);
            break;
        }
    }
    if (bogusTransformSnap(player, position))
    {
        State.events.push_back(new CheatDetectedEvent(GetEventPlayer(player.get_PlayerControl()), CHEAT_TELEPORT));
    }
    */

    CustomNetworkTransform_SnapTo(__this, position, minSid, method);
}

static void onGameEnd() {
    LOG_DEBUG("Reset All");
    Replay::Reset();
    State.aumUsers.clear();
    State.MatchEnd = std::chrono::system_clock::now();

    drawing_t& instance = Esp::GetDrawing();
    synchronized(instance.m_DrawingMutex) {
        instance.m_Players = {};
    }
}

void dAmongUsClient_OnGameEnd(AmongUsClient* __this, Object* endGameResult, MethodInfo* method) {
    onGameEnd();
    AmongUsClient_OnGameEnd(__this, endGameResult, method);
}

void dInnerNetClient_DisconnectInternal(InnerNetClient* __this, DisconnectReasons__Enum reason, String* stringReason, MethodInfo* method) {
    // IsInGame() || IsInLobby()
    if (__this->fields.GameState == InnerNetClient_GameStates__Enum::Started
        || __this->fields.GameState == InnerNetClient_GameStates__Enum::Joined
        || __this->fields.GameMode == GameModes__Enum::FreePlay) {
        onGameEnd();
    }
    InnerNetClient_DisconnectInternal(__this, reason, stringReason, method);
}

void dInnerNetClient_EnqueueDisconnect(InnerNetClient* __this, DisconnectReasons__Enum reason, String* stringReason, MethodInfo* method) {
    if (!IsHost() || reason != DisconnectReasons__Enum::Banned) {
        return InnerNetClient_EnqueueDisconnect(__this, reason, stringReason, method);
    }
    if (reason == DisconnectReasons__Enum::Banned) {
        LOG_INFO("Blocked ban");
    }
}

void dUdpConnection_HandleKeepAlive(UdpConnection* __this, Object* state, MethodInfo* method) {
    if (__this->fields._._._state == (int32_t)ConnectionState__Enum::Connected
        && (std::this_thread::yield(), __this->fields.pingsSinceAck >= 3)) {
        std::this_thread::yield();
        LOG_INFO(std::format("pingsSinceAck {}", __this->fields.pingsSinceAck));
    }
    app::UdpConnection_HandleKeepAlive(__this, state, method);
}

void dUnityUdpClientConnection_ConnectAsync(void* __this, Byte__Array* bytes, MethodInfo* method) {
    auto conn = reinterpret_cast<UdpConnection*>(__this);
    conn->fields._MissingPingsUntilDisconnect_k__BackingField = 18;
    conn->fields.DisconnectTimeoutMs = (std::min)(30000, 1500 * conn->fields._MissingPingsUntilDisconnect_k__BackingField);
    app::UnityUdpClientConnection_ConnectAsync(__this, bytes, method);
}