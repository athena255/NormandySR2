#pragma once
// CheatManager.h
//
// Monitors the cheats that the user specifies
//
#include "GameManager.h"
#include "Cheats.h"
#include <unordered_map>

class CheatManager
{
public:
	CheatManager();
	~CheatManager();

	// Checks for whether we should enable or disable cheats
	VOID CheckInput();

	NTSTATUS status{};
	std::unordered_map<CheatClass, std::unique_ptr<Cheats>> cheats{};
private:
};

