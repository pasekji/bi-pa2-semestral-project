#include "CPlayerRogue.h"
#include "CApplication.h"
#include "CAttack.h"



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

bool CPlayerRogue::accept(CAttack* attack)
{
    attack->visit(this);
    return true;
}

void CPlayerRogue::showStats() const
{
    return;
}