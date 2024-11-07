#pragma once

#include <cstdint>
#include <vector>
#include <mutex>
#include <atomic>

namespace CommonStorage
{
	extern std::atomic<bool> IS_ALIVE;
	extern std::vector<uintptr_t> ENEMY_PTRS;
};

void ADD_ENEMY_POINTER(uintptr_t ptr);

void CLEAR_ENEMY_LIST();

void GET_ENTITY_LIST(std::vector<uintptr_t>& storage);