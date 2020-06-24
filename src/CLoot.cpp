#include "CLoot.h"
#include "CPickup.h"

bool CLoot::acceptTarget(std::shared_ptr<CPickup> pickup)
{
    pickup->visitTarget(m_sharedThis);
    return true;
}