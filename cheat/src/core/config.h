#pragma once

#include <filesystem>
#include <string>
#include <conio.h>
#include <iostream>
#include <Windows.h>
#include <fstream>
#include "..\..\ext\encrypt\encrypt.h"
#include "..\..\ext\json\json.hpp"

namespace config {
	void Setup() noexcept;

	inline std::string key = "HWJHGRGRKEUC";

	inline bool menuOpen = false;
}