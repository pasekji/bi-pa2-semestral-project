#include "CLoot.h"
#include "CPickup.h"

bool CLoot::acceptTarget(CPickup* pickup)
{
    pickup->visitTarget(this);
    return true;
}