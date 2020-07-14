#include "pch.h"
#include "TriggerBot.h"
#include "globals.h"
VOID TriggerBot::execute()
{
	Entity* localPlayer = g::gameMan->GetLocalPlayer();
	UINT idx = localPlayer->GetEntityInCrossHairs();
	Entity* target = static_cast<Entity*>(g::iClientEntityList->GetClientEntity(idx));
	if (g::gameMan->EntityIsValid(target) && localPlayer->GetTeam() != target->GetTeam())
	{
		g::userCmd->buttons |= IN_ATTACK;
	}
}

