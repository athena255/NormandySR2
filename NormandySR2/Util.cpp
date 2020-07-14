#include "pch.h"
#include "Util.h"
#include "globals.h"

Vector ExtrapolateTick(Vector p0, Vector v0)
{
    return p0 + (v0 * g::globalVars->interval_per_tick);
}
