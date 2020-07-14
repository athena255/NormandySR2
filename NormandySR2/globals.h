#pragma once
#include "Util.h"
#include "sdk.hpp"
#include "CheatManager.h"
namespace g {
	extern IBaseClientDLL* iBaseClientDLL;
	extern IClientEntityList* iClientEntityList;
	extern IVEngineClient* iVEngineClient;
	extern IEngineTrace* iEngineTrace;
	extern IClientMode* iClientMode;
	extern VTHook iClientModeVT;
	extern CUserCmd* userCmd;
	extern CheatManager* cheatMan;
	extern GameManager* gameMan;
	extern CGlobalVarsBase* globalVars;
}

