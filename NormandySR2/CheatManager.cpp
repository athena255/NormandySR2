#include "pch.h"
#include "globals.h"
#include "CheatManager.h"
#include "Wallhack.h"
#include "Aimbot.h"
#include "TriggerBot.h"
#include "AutoStrafe.h"
CheatManager::CheatManager()
{
	// Initialize cheats
	cheats[CheatClass::Wallhack] = std::make_unique<Wallhack>();
	cheats[CheatClass::Aimbot] = std::make_unique<Aimbot>();
	cheats[CheatClass::AutoStrafe] = std::make_unique<AutoStrafe>();
	cheats[CheatClass::Trigger] = std::make_unique<TriggerBot>();
}

CheatManager::~CheatManager()
{
	for (auto& c : g::cheatMan->cheats)
		c.second.reset();
}

VOID CheatManager::CheckInput()
{
	if (GetAsyncKeyState(TOGGLE_AIMBOT) & 1)
	{
		cheats[CheatClass::Aimbot]->toggleCheat();
	}
	if (GetAsyncKeyState(TOGGLE_WALLHACK) & 1)
	{
		cheats[CheatClass::Wallhack]->toggleCheat();
	}
	if (GetAsyncKeyState(TOGGLE_AUTOSTRAFE) & 1)
	{
		cheats[CheatClass::AutoStrafe]->toggleCheat();
	}
	if (GetAsyncKeyState(TOGGLE_TRIGGER) & 1)
	{
		cheats[CheatClass::Trigger]->toggleCheat();
	}
	if (GetAsyncKeyState(PANIC) & 1)
	{
		g::gameMan->~GameManager();
	}
}
