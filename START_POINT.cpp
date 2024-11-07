#include "START_POINT.h"


/*void Entity_Finder(std::vector<uintptr_t> ENEMY_PTRS, uintptr_t CLIENT)
{
	ENEMY_PTRS.clear();
	uintptr_t ENTITY_LIST = *(uintptr_t*)(CLIENT + cs2_dumper::offsets::client_dll::dwEntityList);
	if (!ENTITY_LIST) return;

	uintptr_t LOCAL_PLAYER = *(uintptr_t*)(CLIENT + cs2_dumper::offsets::client_dll::dwLocalPlayerPawn);

	for (int i = 0; i <= 64; ++i)
	{
		uintptr_t list_entry1 = *(uintptr_t*)(ENTITY_LIST + (8 * (i & 0x7FFF) >> 9) + 16);

		uintptr_t playerController = *(uintptr_t*)(list_entry1 + 120 * (i & 0x1FF));

		uint32_t playerPawn = *(uint32_t*)(playerController + cs2_dumper::schemas::client_dll::CCSPlayerController::m_hPlayerPawn);

		uintptr_t list_entry2 = *(uintptr_t*)(ENTITY_LIST + 0x8 * ((playerPawn & 0x7FFF) >> 9) + 16);

		uintptr_t pCSPlayerPawnPtr = *(uintptr_t*)(list_entry2 + 120 * (playerPawn & 0x1FF));

		int health = *(int*)(pCSPlayerPawnPtr + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iHealth);

		if (health <= 0 || health > 100)
			continue;

		int team = *(int*)(pCSPlayerPawnPtr + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum);

		if (team == *(int*)(LOCAL_PLAYER + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum))
			continue;

		ENEMY_PTRS.push_back(pCSPlayerPawnPtr);
	}

	return;
}*/

void Entity_Finder(std::vector<uintptr_t>& ENEMY_PTRS, uintptr_t CLIENT)
{
	//ENEMY_PTRS.clear();
	CLEAR_ENEMY_LIST();

	uintptr_t LOCALPLAYER = *(uintptr_t*)(CLIENT + cs2_dumper::offsets::client_dll::dwLocalPlayerPawn);
	/*int Health = *(int*)(LOCALPLAYER + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iHealth);*/

	/*f (Health < 1 || Health > 100) CommonStorage::IS_ALIVE.store(false);
	else CommonStorage::IS_ALIVE.store(true);*/

	int TEAM = *(int*)(LOCALPLAYER + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum);

	uintptr_t EntityList = *(uintptr_t*)(CLIENT + cs2_dumper::offsets::client_dll::dwEntityList);
	if (!EntityList) return;

	uintptr_t ListEntry = *(uintptr_t*)(EntityList + 0x10); //check

	for (int i = 1; i < 64; i++)
	{
		if (!ListEntry) continue;

		uintptr_t CurrentController = *(uintptr_t*)(ListEntry + (i * 0x78));
		if (!CurrentController) continue;

		int PawnHandle = *(int*)(CurrentController + cs2_dumper::schemas::client_dll::CCSPlayerController::m_hPlayerPawn);
		if (!PawnHandle) continue;

		uintptr_t ListEntry2 = *(uintptr_t*)(EntityList + (0x8 * ((PawnHandle & 0x7FFF) >> 9) + 0x10));

		uintptr_t PawnCurrent = *(uintptr_t*)(ListEntry2 + (0x78 * (PawnHandle & 0x1FF)));
		if (TEAM == *(int*)(PawnCurrent + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum)) continue;
		if (*(int*)(PawnCurrent + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iHealth) < 1) continue;

		//ENEMY_PTRS.push_back(PawnCurrent);
		ADD_ENEMY_POINTER(PawnCurrent);
	}

	return;
}