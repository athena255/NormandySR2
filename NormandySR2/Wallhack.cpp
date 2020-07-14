#include "pch.h"
#include "Wallhack.h"
#include "Aimbot.h"
#include "globals.h"
typedef struct _GLOW {
	Entity* m_hEntity;
	float r;
	float g;
	float b;
	float a;

	char unknown[4];
	float flUnk;
	float BloomAmount;
	float localplayeriszeropoint3;

	bool RenderWhenOccluded;
	bool RenderWhenUnoccluded;
	bool FullBloomRender;
	char cUnk[1];

	int FullBloomStencilTestValue;
	int GlowStyle;
} GLOW, *PGLOW;

VOID Wallhack::execute()
{
	Entity* localPlayer = g::gameMan->GetLocalPlayer();
	UINT friendlyTeam = localPlayer->GetTeam();
	LPVOID glowMan = g::gameMan->GetGlowManager();
	for (INT i = 0; i < g::iVEngineClient->GetMaxClients(); ++i)
	{
		Entity* entity = g::gameMan->GetEntity(i);
		if (g::gameMan->EntityIsValid(entity) && entity != localPlayer)
			SetEntityGlow(entity, entity->GetTeam() == friendlyTeam, glowMan);
	}
}

VOID Wallhack::SetEntityGlow(Entity* ent, BOOL isFriendly, LPVOID glowMan)
{
	UINT glowIdx = ent->GetGlowIndex();
	BOOL visible = ent->IsVisible(ECSPlayerBones::HEAD_0);
	PGLOW pGlow = reinterpret_cast<PGLOW>(reinterpret_cast<LPBYTE>(glowMan) + glowIdx * 0x38);
	if (static_cast<Aimbot*>(g::cheatMan->cheats[CheatClass::Aimbot].get())->targetEntity == ent)
	{
		pGlow->r = 1.0f;
		pGlow->b = 0.0f;
		pGlow->g = 0.0f;
	}
	else if (isFriendly)
	{
		pGlow->r = 0.0f;
		pGlow->b = (visible ? .9f : .78f);
		pGlow->g = .235f;
	}
	else
	{
		pGlow->r = (visible ? .9f : .78f);;
		pGlow->b = .78f;
		pGlow->g = .235f;
	}
	pGlow->a = 1.0f;
	pGlow->RenderWhenOccluded = true;
	pGlow->RenderWhenUnoccluded = false;
	pGlow->BloomAmount = ((visible && !isFriendly) ? 1.0f : .5f);
	pGlow->FullBloomRender = false;
	pGlow->FullBloomStencilTestValue = 0;
}
