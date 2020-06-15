#include "CPlayerMage.h"
#include "CApplication.h"
#include "CAttack.h"


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

bool CPlayerMage::accept(CAttack* attack)
{
    attack->visit(this);
    return true;
}

void CPlayerMage::showStats() const
{
    return;
}