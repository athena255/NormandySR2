#include "pch.h"
#include "GameManager.h"
#include "Cheats.h"
#include "globals.h"

VOID Cheats::toggleCheat()
{
	isCheatEnabled = ~isCheatEnabled;
}

BOOL Cheats::shouldCheat()
{
	// Obviously, don't cheat if this cheat is not enabled
	if (!isCheatEnabled)
		return FALSE;
	// Obviously, don't cheat if someone is taking a screenshot
	if (g::iVEngineClient->IsTakingScreenshot())
	{
		toggleCheat();
		return FALSE;
	}
	Entity* localPlayer = g::gameMan->GetLocalPlayer();
	// If we are not in game or if we are dead or if we are about to die, then turn off cheat
	if (!(g::gameMan->isUserInGame() && localPlayer && localPlayer->isAlive() && localPlayer->GetHealth() > 2))
	{
		toggleCheat();
		return FALSE;
	}
	return TRUE;
}