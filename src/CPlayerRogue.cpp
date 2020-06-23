#include "CPlayerRogue.h"
#include "CApplication.h"
#include "CPrimaryAttack.h"
#include "CPickup.h"


extern CApplication application;

CPlayerRogue::CPlayerRogue(WINDOW* objectSpace, int posY, int posX) : CPlayer(objectSpace, posY, posX)
{
    halfdelay(1);
    m_inventorySize = 10;
    m_speed = 1;
    m_inventory = new CInventory(m_inventorySize);
}

int CPlayerRogue::getAction()
{
    // TODO
    return 0;
}

bool CPlayerRogue::interactWith()
{
    // TODO
    return false;
}

void CPlayerRogue::showStats() const
{
    return;
}

bool CPlayerRogue::updateSource(CPickup* pickup)
{
    pickup->updateSource(this);
    return true;
}

bool CPlayerRogue::acceptSource(CPickup* pickup)
{
    pickup->visitSource(this);
    return true;
}

bool CPlayerRogue::acceptTarget(CPickup* pickup)
{
    return false;
}