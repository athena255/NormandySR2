#pragma once
#include "GameManager.h"
#include "Cheats.h"

class Wallhack : public Cheats {
public:
	// Execute this hack for the current tick
	VOID execute() override;
	VOID SetEntityGlow(Entity* ent, BOOL isFriendly, LPVOID glowMan);
};

