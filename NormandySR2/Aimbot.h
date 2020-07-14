#pragma once
#include "Cheats.h"
class Aimbot : public Cheats
{
public:
	VOID execute() override;
	// Updates targetEntity to the entity in our crosshairs if that entity is an enemy
	VOID GetCrosshairsTarget();
	// Updates targetEntity to the one closes to our FOV
	VOID FindVisibleTarget();
	// Calculate the FOV between our aim angles and the location of ent
	float CalcLocalFOV(Entity* ent);
	// The current target entity
	Entity* targetEntity{};
	// Default hit box is chest
	static constexpr UINT HitBox = ECSPlayerBones::HEAD_0;
private:
	// True if the targetEntity is in our crosshairs
	BOOL wouldHit{};
	// Pointer to the local player
	Entity* localPlayer{};
};

