#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "il2cpp-init.h"
#include "main.h"
#if _VERSION
#include "version.h"
#endif

static HANDLE s_hThread = nullptr;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
#if _VERSION
		s_hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Load, hModule, NULL, NULL);
#else
		s_hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Run, hModule, NULL, NULL);
#endif
		break;
	case DLL_PROCESS_DETACH:
		if (hUnloadEvent) {
			SetEvent(hUnloadEvent);
		}
		if (s_hThread) {
			// FIXME: Don't wait too long(100ms should be enough)
			WaitForSingleObject(s_hThread, 100);
			CloseHandle(s_hThread);
			s_hThread = nullptr;
		}
#if _VERSION
		if (version_dll)
			FreeLibrary(version_dll);
#endif
		break;
	}
	return TRUE;
}