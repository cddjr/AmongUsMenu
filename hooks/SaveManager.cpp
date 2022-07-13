#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"
#include "game.h"

bool dSaveManager_GetPurchase(String* itemKey, String* bundleKey, MethodInfo* method)
{
	return true;
}

void dSaveManager_set_AccountLoginStatus(EOSManager_AccountLoginStatus__Enum value, MethodInfo* method) {
	app::SaveManager_set_AccountLoginStatus(value, method);
	synchronized(State.nameMutex) {
		State.userName = convert_from_string(app::SaveManager_get_PlayerName(nullptr));
	}
}

void dSaveManager_set_PlayerName(String* value, MethodInfo* method) {
	app::SaveManager_set_PlayerName(value, method);
	synchronized(State.nameMutex) {
		State.userName = convert_from_string(app::SaveManager_get_PlayerName(nullptr));
	}
}