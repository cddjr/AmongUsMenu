#include "pch-il2cpp.h"
#include "_hooks.h"
#include "detours/detours.h"
#include "DirectX.h"
#include <iostream>
#include "main.h"
#include "SignatureScan.hpp"
#include "game.h"
#include "logger.h"

using namespace Game;

bool HookFunction(PVOID* ppPointer, PVOID pDetour, const char* functionName) {
	if (const auto error = DetourAttach(ppPointer, pDetour); error != NO_ERROR) {
		STREAM_ERROR("Failed to hook " << functionName << ", error " << error);
		return false;
	}
	//std::cout << "Hooked " << functionName << std::endl;
	return true;
}

bool UnhookFunction(PVOID* ppPointer, PVOID pDetour, const char* functionName) {
	if (const auto error = DetourDetach(ppPointer, pDetour); error != NO_ERROR) {
		STREAM_ERROR("Failed to unhook " << functionName << ", error " << error);
		return false;
	}
	//std::cout << "Unhooked " << functionName << std::endl;
	return true;
}

static std::vector<std::tuple<PVOID*/*ppPointer*/, PVOID/*pDetour*/, const char*/*functionName*/>> s_hooks;

#define HOOKFUNC(n) s_hooks.emplace_back(std::forward_as_tuple(&(PVOID&)n, d ## n, #n))

void DetourInitilization() {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	directx11 d3d11 = directx11();
	if (!d3d11.presentFunction) {
		LOG_ERROR("Unable to retrieve IDXGISwapChain::Present method");
		return;
	} else {
		// Attempting to hook the Steam overlay
		do {
			if (oPresent)
				break;
			HMODULE hModule = GetModuleHandleA("GameOverlayRenderer.dll");
			if (!hModule)
				break;
			oPresent = SignatureScan<D3D_PRESENT_FUNCTION>("55 8B EC 53 8B 5D ? F6 C3 01 74 ? 53 FF 75 ? FF 75 ? FF 15 ? ? ? ? 5B 5D C2", hModule);
			if (oPresent)
				break;
			if (MessageBox(NULL,
				L"Failed to hook the Steam overlay D3DPresent function.\nThis may cause the menu to be visible to streaming applications.  Do you wish to continue?",
				L"Error",
				MB_YESNO | MB_ICONWARNING) == IDNO)
			{
				if (hUnloadEvent)
					SetEvent(hUnloadEvent); //Might as well unload the DLL if we're not going to render anything
				return;
			}
			oPresent = d3d11.presentFunction;
		} while (0);
		// Attempting to hook the Epic overlay
		do {
			if (oPresent)
				break;
			HMODULE hModule = GetModuleHandleA("EOSOVH-Win32-Shipping.dll");
			if (!hModule)
				break;
			oPresent = SignatureScan<D3D_PRESENT_FUNCTION>("56 8B 74 24 08 8D 44 24 08 6A 01 56 50 E8 ? ? ? ? 83 C4 0C 83 7C 24 ? ? 74 1C 8D 44 24 08 56 50 E8 ? ? ? ? 8B 44 24 10 83 C4 08 85 C0 74 06 8B 08 50 FF 51 08 FF 74 24 10 A1 ? ? ? ? FF 74 24 10 56 FF D0 5E C2 0C 00", hModule);
			if (oPresent)
				break;
			if (MessageBox(NULL,
				L"Failed to hook the Epic overlay D3DPresent function.\nThis may cause the menu to be visible to streaming applications.  Do you wish to continue?",
				L"Error",
				MB_YESNO | MB_ICONWARNING) == IDNO)
			{
				if (hUnloadEvent)
					SetEvent(hUnloadEvent); //Might as well unload the DLL if we're not going to render anything
				return;
			}
			oPresent = d3d11.presentFunction;
		} while (0);
		if (!oPresent)
			oPresent = d3d11.presentFunction;
	}

	HOOKFUNC(SceneManager_Internal_ActiveSceneChanged);
	HOOKFUNC(PlayerControl_FixedUpdate);
	HOOKFUNC(PlayerControl_RpcSyncSettings);
	HOOKFUNC(PlayerControl_Shapeshift);
	HOOKFUNC(PlayerControl_ProtectPlayer);
	HOOKFUNC(MeetingHud_Update);
	HOOKFUNC(MeetingHud_PopulateResults);
	HOOKFUNC(ShipStatus_CalculateLightRadius);
	HOOKFUNC(AirshipStatus_CalculateLightRadius);
	HOOKFUNC(ShipStatus_OnEnable);
	HOOKFUNC(PolusShipStatus_OnEnable);
	HOOKFUNC(AirshipStatus_OnEnable);
	HOOKFUNC(Vent_CanUse);
	HOOKFUNC(Vent_EnterVent);
	HOOKFUNC(Vent_ExitVent);
	HOOKFUNC(StatsManager_get_AmBanned);
	HOOKFUNC(StatsManager_get_BanMinutesLeft);
	HOOKFUNC(StatsManager_get_BanPoints);
	HOOKFUNC(AutoOpenDoor_DoUpdate);
	HOOKFUNC(ChatBubble_SetName);
	HOOKFUNC(ChatController_AddChat);
	HOOKFUNC(ChatController_SetVisible);
	HOOKFUNC(HudManager_ShowMap);
	HOOKFUNC(HudManager_Update);
	HOOKFUNC(Camera_ScreenToWorldPoint);
	HOOKFUNC(KeyboardJoystick_Update);
	HOOKFUNC(ScreenJoystick_FixedUpdate);
	HOOKFUNC(PlainDoor_SetDoorway);
	HOOKFUNC(GameOptionsData_Deserialize);
	HOOKFUNC(GameOptionsData_Deserialize_1);
	HOOKFUNC(PlayerControl_MurderPlayer);
	HOOKFUNC(PlayerControl_CompleteTask);
	//HOOKFUNC(PlayerControl_CmdReportDeadBody);
	//HOOKFUNC(PlayerControl_ReportDeadBody);
	HOOKFUNC(PlayerControl_StartMeeting);
	HOOKFUNC(RoleManager_SelectRoles);
	HOOKFUNC(RoleManager_AssignRolesForTeam);
	HOOKFUNC(RoleManager_AssignRolesFromList);
	HOOKFUNC(PlayerControl_HandleRpc);
	HOOKFUNC(Renderer_set_enabled);
	HOOKFUNC(MeetingHud_Awake);
	HOOKFUNC(MeetingHud_Close);
	HOOKFUNC(InnerNetClient_Update);
	HOOKFUNC(AmongUsClient_OnPlayerLeft);
	HOOKFUNC(CustomNetworkTransform_SnapTo);
	HOOKFUNC(Constants_ShouldFlipSkeld);
	HOOKFUNC(LobbyBehaviour_Start);
	HOOKFUNC(GameObject_SetActive);
	HOOKFUNC(NoShadowBehaviour_LateUpdate);
	HOOKFUNC(FollowerCamera_Update);
	HOOKFUNC(DoorBreakerGame_Start);
	HOOKFUNC(DoorCardSwipeGame_Begin);
	HOOKFUNC(Debug_Log);
	HOOKFUNC(Debug_LogError);
	HOOKFUNC(Debug_LogException);
	HOOKFUNC(Debug_LogWarning);
	HOOKFUNC(VersionShower_Start);
	HOOKFUNC(EOSManager_LoginFromAccountTab);
	HOOKFUNC(EOSManager_InitializePlatformInterface);
	HOOKFUNC(EOSManager_IsFreechatAllowed);
	HOOKFUNC(ChatController_Update);
	HOOKFUNC(InnerNetClient_EnqueueDisconnect);
	HOOKFUNC(PlayerPhysics_FixedUpdate);
	HOOKFUNC(SaveManager_GetPurchase);
	HOOKFUNC(PlayerControl_TurnOnProtection);
	HOOKFUNC(AmongUsClient_OnGameEnd);
	HOOKFUNC(InnerNetClient_DisconnectInternal);
	HOOKFUNC(UdpConnection_HandleKeepAlive);
	HOOKFUNC(UnityUdpClientConnection_ConnectAsync);
	HOOKFUNC(VentilationSystem_Deserialize);
	HOOKFUNC(AccountManager_UpdateKidAccountDisplay);
	HOOKFUNC(PlayerStorageManager_OnReadPlayerPrefsComplete);
	HOOKFUNC(EOSManager_UpdatePermissionKeys);
	HOOKFUNC(SaveManager_set_AccountLoginStatus);
	HOOKFUNC(SaveManager_set_PlayerName);

	s_hooks.emplace_back(std::forward_as_tuple(&(PVOID&)oPresent, dPresent, "D3D_PRESENT_FUNCTION"));

	for (auto& hook : s_hooks) {
		if (!HookFunction(std::get<0>(hook), std::get<1>(hook), std::get<2>(hook)))
			return;
	}

	DetourTransactionCommit();
}

void DetourUninitialization()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	for (auto& hook : s_hooks) {
		if (auto ppPointer = std::get<0>(hook)) {
			UnhookFunction(ppPointer, std::get<1>(hook), std::get<2>(hook));
		}
	}

	DetourTransactionCommit();
	DirectX::Shutdown();
}