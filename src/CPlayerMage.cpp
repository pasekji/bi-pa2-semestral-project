#include "CPlayerMage.h"
#include "CApplication.h"
#include "CPrimaryAttack.h"
#include "CPickup.h"

extern CApplication application;

CPlayerMage::CPlayerMage(int posY, int posX) : CPlayer(posY, posX)
{
    m_sharedDerived = std::dynamic_pointer_cast<CPlayerMage> (m_sharedThis);
    halfdelay(1);
    m_inventorySize = 15;
    m_speed = 1;
    m_inventory.reset(new CInventory(m_inventorySize));
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

bool CPlayerMage::updateSource(std::shared_ptr<CPickup> pickup)
{
    pickup->updateSource(m_sharedDerived);    
    return true;
}

bool CPlayerMage::acceptSource(std::shared_ptr<CPickup> pickup)
{
    pickup->visitSource(m_sharedDerived);
    return true;
}

bool CPlayerMage::acceptTarget(std::shared_ptr<CPickup> pickup)
{
    return false;
}

std::shared_ptr<CGameObject> loadPlayerMage(ifstream& is)
{
    int posX;
    is >> posX;
    int posY;
    is >> posY;

    std::shared_ptr<CGameObject> result;
    result.reset(new CPlayerMage(posY, posX));
    return result;
}