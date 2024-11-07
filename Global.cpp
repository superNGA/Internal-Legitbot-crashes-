#include "Global.h"

namespace CommonStorage
{
	std::mutex DATA_PROTECTOR;
	std::atomic<bool> IS_ALIVE;
	std::vector<uintptr_t> ENEMY_PTRS;
};

void ADD_ENEMY_POINTER(uintptr_t ptr)
{
	std::lock_guard<std::mutex> lock(CommonStorage::DATA_PROTECTOR);
	CommonStorage::ENEMY_PTRS.push_back(ptr);
}

void CLEAR_ENEMY_LIST()
{
	std::lock_guard<std::mutex> lock(CommonStorage::DATA_PROTECTOR);
	CommonStorage::ENEMY_PTRS.clear();
}

void GET_ENTITY_LIST(std::vector<uintptr_t>& storage)
{
	storage.clear();
	std::lock_guard<std::mutex> lock(CommonStorage::DATA_PROTECTOR);
	storage = CommonStorage::ENEMY_PTRS;
}