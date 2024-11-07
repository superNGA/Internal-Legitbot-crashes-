#pragma once

#include <Windows.h>
#include <thread>
#include <vector>

#include "Global.h"
#include "Offsets/Client.h"
#include "Offsets/Offset.h"

void Entity_Finder(std::vector<uintptr_t>& ENEMY_PTRS, uintptr_t CLIENT);