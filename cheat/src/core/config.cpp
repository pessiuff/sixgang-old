#include "config.h"

using nlohmann::json;

void CopyToClipBoard(const char* text) {
	int size = ::MultiByteToWideChar(CP_UTF8, 0, text, -1, nullptr, 0);
	if (size < 0) {
		return;
	}

	if (::OpenClipboard(NULL)) {
		::EmptyClipboard();
		HGLOBAL hGlobal = ::GlobalAlloc(GMEM_ZEROINIT | GMEM_MOVEABLE | GMEM_DDESHARE, (size + 1) * sizeof(WCHAR));
		if (hGlobal != NULL) {
			LPWSTR lpszData = (LPWSTR)::GlobalLock(hGlobal);
			if (lpszData != nullptr) {
				::MultiByteToWideChar(CP_UTF8, 0, text, -1, lpszData, size);
				::GlobalUnlock(hGlobal);
				::SetClipboardData(CF_UNICODETEXT, hGlobal);
			}
		}
		::CloseClipboard();
	}
}

void config::Setup() noexcept
{
	while (!std::filesystem::exists("sixgang.json")) {
		try {
			json configJson;
			configJson["menuOpen"] = true;

			std::ofstream config("sixgang.json");
			config << configJson;
			
			config.close();
			printf_s("Config file wasn't found and created with default settings.\n");
		}
		catch (const std::exception& e) {
#ifdef _DEBUG
			printf_s("Exception while creating default config file. %s\n", e.what());
#endif
#ifndef  _DEBUG
			CopyToClipBoard(e.what());
			MessageBoxA(0, "Caught an exception and copied it to your clipboard. Send it to a staff member. The game will close now.", "Exception", MB_OK);
			exit(-1);
#endif
		}
	}
#ifdef _DEBUG
	printf_s("Config file found.\n");
#endif
	try {
		std::ifstream config("sixgang.json");
		json configJson;
		config >> configJson;

		menuOpen = configJson["menuOpen"].get<bool>();

		config.close();
	}
	catch (const std::exception& e) {
#ifdef _DEBUG
		printf_s("Exception while loading config file. %s\n", e.what());
#endif
#ifndef  _DEBUG
		CopyToClipBoard(e.what());
		MessageBoxA(0, "Caught an exception and copied it to your clipboard. Send it to a staff member. The game will close now.", "Exception", MB_OK);
		exit(-1);
#endif
	}
}
