#include "CPlayerRogue.h"
#include "CApplication.h"
#include "CPrimaryAttack.h"
#include "CPickup.h"


extern CApplication application;

CPlayerRogue::CPlayerRogue(int posY, int posX) : CPlayer(posY, posX)
{
    m_sharedDerived = std::dynamic_pointer_cast<CPlayerRogue> (m_sharedThis);
    halfdelay(2);
    m_inventorySize = 10;
    m_speed = 1;
    m_health = 75;
    m_currentHealth = m_health;
    m_energy = 100;
    m_currentEnergy = m_energy;
    m_agility = 7;
    m_energyForStep = 2;
    m_energyRegain = 4;
    m_primaryAttackType = MELEE;
    m_inventory.reset(new CInventory(m_inventorySize));
}

int CPlayerRogue::getAction()
{
    defaultStep(m_move);

    if(!isDead())
    {
        if(toupper(m_move) == 'Q')
            quickJump();
        if(!defaultMove(m_move))
            if(!interactWith())
                rest();
    }
    return m_move;
}

void CPlayerRogue::quickJump()
{
    return;
}

bool CPlayerRogue::interactWith()
{
    bool used = false;

    std::shared_ptr<CGameObject> target = defaultGetTarget();

    if(target == nullptr)
        return used;
        
    switch (m_move)
    {
        case 'E':
        case 'e':
            if(m_currentEnergy >= m_agility)
                roguePrimaryAttack(target);
            used = true;
            break;

        case 'P':
        case 'p':
            itemPickup(target);
            used = true;
            break;

        default:
            break;
    }

    return used;
}

bool CPlayerRogue::roguePrimaryAttack(std::shared_ptr<CGameObject> target)
{

    return false;
}

void CPlayerRogue::showStats() const
{
    return;
}

bool CPlayerRogue::updateSource(std::shared_ptr<CPickup> pickup)
{
    pickup->updateSource(m_sharedDerived);
    return true;
}

bool CPlayerRogue::acceptSource(std::shared_ptr<CPickup> pickup)
{
    pickup->visitSource(m_sharedDerived);
    return true;
}

bool CPlayerRogue::acceptTarget(std::shared_ptr<CPickup> pickup)
{
    return false;
}