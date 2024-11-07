#pragma once

#include <Windows.h>
#include <thread>
#include <vector>
//#include <iostream>

#include "Global.h"
#include "Math/Vector.h"
#include "Offsets/Client.h"
#include "Offsets/Offset.h"

extern std::vector<Vector> PLAYER_SCREEN_POSITION;
extern std::vector<uintptr_t> ENEMY_PTRStemp;
extern int SMOOTHING_FACTOR;
extern float FOV_RADIUS;

Vector findClosest(const std::vector<Vector> playerPositions);

void MoveMouseToPlayer(Vector position);

void EXECUTE(uintptr_t CLIENT);

