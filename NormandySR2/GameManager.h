#pragma once
// GameManager.h
//
// Monitors the state of the game
//

#include "Settings.h"
#include "sdk.hpp"
#include "Entity.h"

class GameManager
{
public:
	GameManager();
	~GameManager();
	// True if the user is in game
	BOOL isUserInGame();
	Entity* GetEntity(UINT entityIndex);
	BOOL EntityIsValid(Entity* ent);

	// Return the local player in the entity list
	Entity* GetLocalPlayer();
	// Return the glow manager object
	LPVOID GetGlowManager();

	NTSTATUS status{};
	// Base address of engine.dll
	LPVOID engineBaseAddr{};
	// Address of clientState in engine.dll
	LPVOID clientStateAddr{};
	// Base address of client.dll
	LPVOID clientBaseAddr{};
};

