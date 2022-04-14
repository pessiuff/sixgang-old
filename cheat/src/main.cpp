#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <thread>

// expose our cheat to main.cpp
#include "core/hooks.h"

#include "core/config.h"
#include "core/gui.h"

// setup our cheat & unload it when exit key is pressed
DWORD WINAPI Setup(LPVOID lpParam)
{
#ifdef _DEBUG
	// create console for debugging in windows using freopen_s
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
	freopen_s((FILE**)stderr, "CONOUT$", "w", stderr);
	// set console title
	SetConsoleTitleA("[DEBUG]");
#endif

	memory::Setup();		// find signatures
	interfaces::Setup();    // capture interfaces
	netvars::Setup();		// dump latest offsets
	gui::Setup();           // setup gui
	hooks::Setup();			// place hooks

	config::Setup();        // setup config

	// sleep our thread until unload key is pressed
	while (!GetAsyncKeyState(VK_END))
		std::this_thread::sleep_for(std::chrono::milliseconds(200));

	std::this_thread::sleep_for(std::chrono::milliseconds(50));

#ifdef _DEBUG
	// close console
	fclose(stdout);
	fclose(stdin);
	fclose(stderr);
	FreeConsole();
#endif

	// unload library
	FreeLibraryAndExitThread(static_cast<HMODULE>(lpParam), EXIT_SUCCESS);
}

BOOL APIENTRY DllMain(HMODULE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	// dll is being loaded
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		// disable thread notifications
		DisableThreadLibraryCalls(hinstDLL);

		// create our "Setup" thread
		const HANDLE hThread = CreateThread(
			nullptr,
			NULL,
			Setup,
			hinstDLL,
			NULL,
			nullptr
		);

		// free thread handle because we have no use for it
		if (hThread)
			CloseHandle(hThread);
	} else if (fdwReason == DLL_PROCESS_DETACH) {
		// dll is being unloaded
		hooks::Destroy();		// restore hooks
		gui::Destroy();		// restore gui
	}

	// successful DLL_PROCESS_ATTACH
	return TRUE;
}
