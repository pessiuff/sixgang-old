#pragma once

#include <filesystem>
#include <string>
#include <iostream>
#include <Windows.h>
#include <fstream>
#include "..\..\ext\json\json.hpp"

namespace config {
	void Setup() noexcept;

	inline bool menuOpen = false;
}