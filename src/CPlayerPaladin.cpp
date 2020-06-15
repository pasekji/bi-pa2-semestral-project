#include "CPlayerPaladin.h"
#include "CApplication.h"
#include "CPrimaryAttack.h"


extern CApplication application;

CPlayerPaladin::CPlayerPaladin(WINDOW* objectSpace, int posY, int posX) : CPlayer(objectSpace, posY, posX)
{
    halfdelay(1);
    m_inventorySize = 20;
    m_speed = 1;
    m_inventory = new CInventory(m_inventorySize);
}

int CPlayerPaladin::getAction()
{
    defaultStep(this->m_move);                  // sprint is not availiable with paladin
    
    if(!defaultMove(this->m_move))
        interactWith();
  
    return this->m_move;
}

bool CPlayerPaladin::interactWith()
{
    int tmppos;
    std::pair<int, int> pair;

    CGameObject* target = nullptr;

    switch (m_objectForm)
    {
        case '^':
            target = application.getGame().getMap()->getTargetObject(pair = std::make_pair(tmppos = m_posY - 1, m_posX));
            break;
    
        case 'v':
            target = application.getGame().getMap()->getTargetObject(pair = std::make_pair(tmppos = m_posY + 1, m_posX));        
            break;

        case '<':
            target = application.getGame().getMap()->getTargetObject(pair = std::make_pair(m_posY, tmppos = m_posX - 1));
            break;

        case '>':
            target = application.getGame().getMap()->getTargetObject(pair = std::make_pair(m_posY, tmppos = m_posX + 1));
            break;

        default:
            break;
    }

    if(target == nullptr)
        return false;
        
    switch (this->m_move)
    {
        case 'E':
        case 'e':
            paladinPrimaryAttack(target);
            break;

        case 'G':
        case 'g':
            break;

        default:
            break;
    }

    return false;
}

bool CPlayerPaladin::accept(CAttack* attack)
{
    attack->visit(this);
    return true;
}

bool CPlayerPaladin::paladinPrimaryAttack(CGameObject* target)
{
    CAttack* attack = new CPrimaryAttack(this, target, SLAIN);
    return true;
}

void CPlayerPaladin::showStats() const
{
    return;
}