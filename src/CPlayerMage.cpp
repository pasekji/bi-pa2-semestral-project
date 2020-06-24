#include "CPlayerMage.h"
#include "CApplication.h"
#include "CPrimaryAttack.h"
#include "CPickup.h"

extern CApplication application;

CPlayerMage::CPlayerMage(int posY, int posX) : CPlayer(posY, posX)
{
    m_sharedDerived = std::dynamic_pointer_cast<CPlayerMage> (m_sharedThis);
    halfdelay(1);
    m_inventorySize = 10;
    m_speed = 1;
    m_health = 90;
    m_currentHealth = m_health;
    m_energy = 110;
    m_currentEnergy = m_energy;
    m_wisdom = 15;
    m_energyForStep = 4;
    m_energyRegain = 3;
    m_primaryAttackType = SPELL;
    m_inventory.reset(new CInventory(m_inventorySize));
}

int CPlayerMage::getAction()
{
    defaultStep(m_move);

    if(!isDead())
    {
        if(!defaultMove(m_move))
            if(!interactWith())
                rest();
    }
    return m_move;
}

bool CPlayerMage::interactWith()
{
    bool used = false;

    std::shared_ptr<CGameObject> target = directionGetTarget();

    if(target == nullptr)
        return used;
        
    switch (m_move)
    {
        case 'E':
        case 'e':
            if(m_currentEnergy >= m_wisdom)
                magePrimaryAttack(target);
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

bool CPlayerMage::magePrimaryAttack(std::shared_ptr<CGameObject> target)
{
    std::shared_ptr<CAttack> attack;
    attack = (new CPrimaryAttack(m_sharedDerived, target, m_primaryAttackType))->getPtr();
    application.getGame()->pushEvent(attack);
    return true;
}

void CPlayerMage::showStats() const
{
    int height, width;
    getmaxyx(application.getGame()->getPlayerWindow(), height, width);
    mvwprintw(application.getGame()->getPlayerWindow(), (height - 14) / 2, (width - strlen("PLAYER")) / 2, "PLAYER ");
    mvwprintw(application.getGame()->getPlayerWindow(), (height - 10) / 2, (width - strlen("Class:     MAGE")) / 2, "Class:     MAGE ");
    mvwprintw(application.getGame()->getPlayerWindow(), (height - 6) / 2, (width - strlen("Experience:  %d") - 2) / 2, "Experience:  %d ", m_currentExp);
    mvwprintw(application.getGame()->getPlayerWindow(), (height - 2) / 2, (width - strlen("Health:    %d/%d") - 2) / 2, "Health:    %d/%d ", m_currentHealth, m_health);
    mvwprintw(application.getGame()->getPlayerWindow(), (height + 2) / 2, (width - strlen("Energy:    %d/%d") - 2) / 2, "Energy:    %d/%d ", m_currentEnergy, m_energy);
    mvwprintw(application.getGame()->getPlayerWindow(), (height + 6) / 2, (width - strlen("Wisdom:     %d") - 1) / 2, "Wisdom:     %d ", m_wisdom);
    wrefresh(application.getGame()->getPlayerWindow());

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

std::shared_ptr<CCharacter> loadPlayerMage(ifstream& is)
{
    int posX;
    is >> posX;
    int posY;
    is >> posY;

    std::shared_ptr<CCharacter> result;
    result.reset(new CPlayerMage(posY, posX));
    return result;
}