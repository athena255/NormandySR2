#include "pch.h"
#include "AutoStrafe.h"
#include "globals.h"

VOID AutoStrafe::execute()
{
    if (g::gameMan->GetLocalPlayer()->GetFlags() & FL_ONGROUND)
        return;
    if (g::userCmd->mousedx < 0)
        g::userCmd->sidemove = -450.0f;
    if (g::userCmd->mousedx > 0)
        g::userCmd->sidemove = 450.0f;
}
