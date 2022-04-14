#pragma once
#include "../util/memory.h"

class IVPanel
{
public:
	constexpr void SetKeyboardInputEnabled(std::uint32_t panel, bool state) {
		return memory::Call<void>(this, 31, panel, state);
	}
	constexpr void SetMouseInputEnabled(std::uint32_t panel, bool state) {
		return memory::Call<void>(this, 32, panel, state);
	}
	constexpr const char* GetName(std::uint32_t panel) noexcept
	{
		return memory::Call<const char*>(this, 36, panel);
	}
};
