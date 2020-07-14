#include "pch.h"
#include "globals.h"
namespace g {
	IBaseClientDLL* iBaseClientDLL;
	IClientEntityList* iClientEntityList;
	IVEngineClient* iVEngineClient;
	IEngineTrace* iEngineTrace;
	IClientMode* iClientMode;
	VTHook iClientModeVT;
	CUserCmd* userCmd;
	CheatManager* cheatMan;
	GameManager* gameMan;
	CGlobalVarsBase* globalVars;
}