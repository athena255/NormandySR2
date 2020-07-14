#include "pch.h"
#include "sdk.hpp"
#include "Entity.h"
#include "Util.h"
#include "csgo.h"
#include "globals.h"
// Entity Definitions
BOOL Entity::isDormant()
{
	return read<BOOL>(this, signatures::m_bDormant);
}
UINT Entity::GetTeam()
{
	return read<UINT>(this, netvars::m_iTeamNum);
}
BOOL Entity::isAlive()
{
	return read<BOOL>(this, netvars::m_lifeState) == 0;
}
UINT Entity::GetGlowIndex()
{
	return read<UINT>(this, netvars::m_iGlowIndex);
}

UINT Entity::GetHealth()
{
	return read<UINT>(this, netvars::m_iHealth);
}

QAngle Entity::GetEyeAngles()
{
	return read<QAngle>(this, netvars::m_angEyeAnglesX);
}
Vector Entity::GetEyePosition()
{
	Vector offset = read<Vector>(this, netvars::m_vecViewOffset);
	return (GetOrigin() + offset);
}
Vector Entity::GetOrigin()
{
	return read<Vector>(this, netvars::m_vecOrigin);
}
Vector Entity::GetBonePosition(UINT bone)
{
	matrix3x4_t bones[128];
	if (SetupBones(bones, 128, 0x100, 0.0f))
	{
		matrix3x4_t boneMatrix = bones[bone];
		return Vector(boneMatrix.m_flMatVal[0][3], boneMatrix.m_flMatVal[1][3], boneMatrix.m_flMatVal[2][3]);
	}
	return Vector{};
}

BOOL Entity::IsVisible(UINT bone)
{
	Ray_t ray;
	trace_t trace;
	auto localPlayer = g::gameMan->GetLocalPlayer();
	ray.Init(localPlayer->GetEyePosition(), this->GetBonePosition(bone));
	CTraceFilter filter;
	filter.pSkip = localPlayer;
	g::iEngineTrace->TraceRay(
		ray,
		MASK_NPCWORLDSTATIC |
		CONTENTS_SOLID |
		CONTENTS_MOVEABLE |
		CONTENTS_MONSTER |
		CONTENTS_WINDOW |
		CONTENTS_DEBRIS |
		CONTENTS_HITBOX,
		&filter,
		&trace
	);
	return (trace.hit_entity == this || trace.fraction > 0.999);
}

UINT Entity::GetEntityInCrossHairs()
{
	return read<UINT>(this, netvars::m_iCrosshairId);
}

UINT Entity::GetFlags()
{
	return read<UINT>(this, netvars::m_fFlags);
}

QAngle Entity::GetPunch()
{
	return read<QAngle>(this, netvars::m_aimPunchAngle);
}

QAngle Entity::GetViewPunch()
{
	return read<QAngle>(this, netvars::m_viewPunchAngle);
}

Vector Entity::GetVelocity()
{
	return read<Vector>(this, netvars::m_vecVelocity);
}

UINT Entity::GetTickBase()
{
	return read<UINT>(this, netvars::m_nTickBase);
}

Vector Entity::GetPredicted(Vector p0)
{
	return ExtrapolateTick(p0, this->GetVelocity());
}
