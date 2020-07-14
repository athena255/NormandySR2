#include "pch.h"
#include "globals.h"
#include "Aimbot.h"

VOID Aimbot::execute()
{
	// Update the local player
	localPlayer = g::gameMan->GetLocalPlayer();
	// Look for entity in crosshairs
	GetCrosshairsTarget();
	// If the crosshairs target is not valid  or we cannot see crosshairs target anymore, then find next best target
	if (! (g::gameMan->EntityIsValid(targetEntity) && targetEntity->IsVisible(HitBox)))
		FindVisibleTarget();

	// Only aim if we are pressing the left mouse button
	if (GetAsyncKeyState(VK_LBUTTON) || GetAsyncKeyState(VK_RBUTTON))
	{
		if (!g::gameMan->EntityIsValid(targetEntity))
			return;
		// Only aim if we would have missed
		if (!wouldHit)
		{
			Vector predicted = targetEntity->GetPredicted(targetEntity->GetBonePosition(HitBox));
			g::userCmd->viewangles = CalcAngle(localPlayer->GetPredicted(localPlayer->GetEyePosition()), predicted).Clamp();
			//g::userCmd->viewangles = CalcAngle(localPlayer->GetEyePosition(), targetEntity->GetBonePosition(HitBox)).Clamp();
		}
	}
}

VOID Aimbot::GetCrosshairsTarget()
{
	UINT idx = localPlayer->GetEntityInCrossHairs();
	Entity* target = static_cast<Entity*>(g::iClientEntityList->GetClientEntity(idx));
	if (g::gameMan->EntityIsValid(target))
	{
		if (localPlayer->GetTeam() != target->GetTeam())
		{
			targetEntity = target;
			wouldHit = true;
		}
	}
	wouldHit = false;
}

VOID Aimbot::FindVisibleTarget()
{
	// A potential target
	Entity* potential{};
	float potFOV = MIN_FOV;

	// Dont help if we have at least 50 health
	if (localPlayer->GetHealth() > MIN_HEALTH)
		return;

	for (UINT i = 0; i < g::iVEngineClient->GetMaxClients(); ++i)
	{
		Entity* ent = static_cast<Entity*>(g::iClientEntityList->GetClientEntity(i));
		// Skip if entity is not valid
		if (!g::gameMan->EntityIsValid(ent))
			continue;
		// Skip if entity is not enemy
		if (ent->GetTeam() == localPlayer->GetTeam())
			continue;
		// Skip if entity is not visible
		if (!ent->IsVisible(HitBox))
			continue;
		// update potential if FOV to new ent < FOV to potential
		float tmpFOV = CalcLocalFOV(ent);
		if (tmpFOV < potFOV)
		{
			potential = ent;
			potFOV = tmpFOV;
		}
	}
	if (potential != nullptr)
		targetEntity = potential;
}

float Aimbot::CalcLocalFOV(Entity* ent)
{
	return FOV(g::userCmd->viewangles, CalcAngle(localPlayer->GetEyePosition(), ent->GetBonePosition(HitBox)));
}


