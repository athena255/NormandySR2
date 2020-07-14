#include "pch.h"
#include "Util.h"
#include "GameManager.h"
#include "csgo.h"
#include "globals.h"
#include "CSGOHooks.h"

GameManager::GameManager()
{
	UNICODE_STRING EngineDll{};
	RtlInitUnicodeString(&EngineDll, ENGINE_DLL);

	// Get engine.dll module
	do {
		status = LdrGetDllHandle(nullptr, nullptr, &EngineDll, &engineBaseAddr);
	} while (!NT_SUCCESS(status));
	clientStateAddr = read<LPVOID>(engineBaseAddr, signatures::dwClientState);

	// Get client.dll module
	UNICODE_STRING ClientDll{};
	RtlInitUnicodeString(&ClientDll, CLIENT_DLL);
	do {
		status = LdrGetDllHandle(nullptr, nullptr, &ClientDll, &clientBaseAddr);
	} while (!NT_SUCCESS(status));

	// Setup interfaces
	g::iClientEntityList = GetInterface<IClientEntityList>((HMODULE)clientBaseAddr, "VClientEntityList003");
	g::iVEngineClient = GetInterface<IVEngineClient>((HMODULE)engineBaseAddr, "VEngineClient014");
	g::iEngineTrace = GetInterface<IEngineTrace>((HMODULE)engineBaseAddr, "EngineTraceClient004");

	g::globalVars = read<CGlobalVarsBase*>(engineBaseAddr, signatures::dwGlobalVars);
	g::iBaseClientDLL = GetInterface<IBaseClientDLL>((HMODULE)clientBaseAddr, "VClient018");
	g::iClientMode = **reinterpret_cast<IClientMode***>((*(uintptr_t**)g::iBaseClientDLL)[10] + 0x5);
	g::iClientModeVT.Init((LPVOID**)g::iClientMode);

	// Hook create move
	g::iClientModeVT.HookFunction(CSGOHooks::NewCreateMove, hookIndex::CreateMove);
}

GameManager::~GameManager()
{
	g::iClientModeVT.Restore();
}

BOOL GameManager::isUserInGame()
{
	return g::iVEngineClient->IsInGame();
}

Entity* GameManager::GetEntity(UINT entityIndex)
{
	return static_cast<Entity*>(g::iClientEntityList->GetClientEntity(entityIndex));
}

BOOL GameManager::EntityIsValid(Entity* ent)
{
	return (ent && ent->isAlive() && !ent->isDormant());
}


Entity* GameManager::GetLocalPlayer()
{
	return GetEntity(g::iVEngineClient->GetLocalPlayer());
}

LPVOID GameManager::GetGlowManager()
{
	return read<LPVOID>(clientBaseAddr, signatures::dwGlowObjectManager);
}
