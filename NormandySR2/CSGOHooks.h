#pragma once
#include "sdk.hpp"
namespace hookIndex {
	constexpr UINT CreateMove = 24;
}

namespace CSGOHooks
{
	using CreateMoveFn = bool(__stdcall*)(float, CUserCmd*);
	bool __stdcall NewCreateMove(float flInputSampleTime, CUserCmd* cmd);
}
