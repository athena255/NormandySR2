#pragma once
#include "GameManager.h"
enum class CheatClass {
	Wallhack,
	Aimbot,
	Trigger,
	AutoStrafe
};
class Cheats
{
public:
	BOOL shouldCheat();
	// Execute the cheat once
	virtual VOID execute() = 0;
	VOID toggleCheat();
	NTSTATUS status{};
protected:
	BOOL isCheatEnabled{};
};

