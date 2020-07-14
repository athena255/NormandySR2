#pragma once
#include "interfaces/IClientEntity.hpp"
class Entity : public IClientEntity
{
public:
	UINT GetTeam();
	BOOL isAlive();
	BOOL isDormant();
	UINT GetGlowIndex();
	UINT GetHealth();
	QAngle GetEyeAngles();
	Vector GetEyePosition();
	Vector GetOrigin();
	UINT GetEntityInCrossHairs();
	Vector GetBonePosition(UINT bone);
	BOOL IsVisible(UINT bone);
	QAngle GetPunch();
	QAngle GetViewPunch();
	UINT GetFlags();
	Vector GetVelocity();
	UINT GetTickBase();
	Vector GetPredicted(Vector p0);
};

