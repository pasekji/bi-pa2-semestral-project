#include "CPlayerMage.h"
#include "CApplication.h"
#include "CPrimaryAttack.h"
#include "CPickup.h"

extern CApplication application;

CPlayerMage::CPlayerMage(WINDOW* objectSpace, int posY, int posX) : CPlayer(objectSpace, posY, posX)
{
    halfdelay(1);
    m_inventorySize = 15;
    m_speed = 1;
    m_inventory = new CInventory(m_inventorySize);
}

int CPlayerMage::getAction()
{
    // TODO
    return 0;
}

bool CPlayerMage::interactWith()
{
    // TODO
    return false;
}

void CPlayerMage::showStats() const
{
    return;
}

bool CPlayerMage::updateSource(CPickup* pickup)
{
    pickup->updateSource(this);
    return true;
}

bool CPlayerMage::acceptSource(CPickup* pickup)
{
    pickup->visitSource(this);
    return true;
}

bool CPlayerMage::acceptTarget(CPickup* pickup)
{
    return false;
}

CGameObject* loadPlayerMage(ifstream& is, WINDOW* objectSpace)
{
    int posX;
    is >> posX;
    int posY;
    is >> posY;
    return new CPlayerMage(objectSpace, posY, posX);
}