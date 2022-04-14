#include "config.h"

using nlohmann::json;

void config::Setup() noexcept
{
	while (!std::filesystem::exists("sixgang.json")) {
		try {
			json configJson;
			configJson["menuOpen"] = true;

			std::string configJson_dump = configJson.dump();
			
			std::string encryptedJson = encrypt::encrypt(configJson_dump, config::key);

			std::ofstream config("sixgang.json");
			config << encryptedJson;
			
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
		std::string encryptedJson;
		config >> encryptedJson;
		std::string decryptedJson = encrypt::decrypt(encryptedJson, config::key);
		auto configJson = json::parse(decryptedJson);

		menuOpen = configJson["menuOpen"].get<bool>();

		config.close();
	}
	catch (const std::exception& e) {
#ifdef _DEBUG
		printf_s("Exception while loading config file. %s\n", e.what());
#endif
#ifndef  _DEBUG
		MessageBoxA(0, "Caught an exception. Send sixgang.log to staff members.", "Exception", MB_OK);
		exit(-1);
#endif
	}
}
