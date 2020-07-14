#include "pch.h"
#include "CSGOHooks.h"
#include "globals.h"

namespace CSGOHooks
{
	bool __stdcall NewCreateMove(float flInputSampleTime, CUserCmd* cmd)
	{
		g::cheatMan->CheckInput();
		// Update the cmd
		g::userCmd = cmd;
		for (auto& c : g::cheatMan->cheats)
		{
			if (c.second->shouldCheat())
				c.second->execute();
		}
		return FALSE;
	}
}