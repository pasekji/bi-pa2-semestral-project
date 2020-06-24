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
        if(!defaultMove(m_move))
            if(!interactWith())
                rest();
    }
    return m_move;
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
    std::shared_ptr<CAttack> attack;
    attack = (new CPrimaryAttack(m_sharedDerived, target, m_primaryAttackType))->getPtr();
    application.getGame()->pushEvent(attack);
    return true;
}

void CPlayerRogue::showStats() const
{
    int height, width;
    getmaxyx(application.getGame()->getPlayerWindow(), height, width);
    mvwprintw(application.getGame()->getPlayerWindow(), (height - 14) / 2, (width - strlen("PLAYER")) / 2, "PLAYER ");
    mvwprintw(application.getGame()->getPlayerWindow(), (height - 10) / 2, (width - strlen("Class:     ROGUE")) / 2, "Class:     ROGUE ");
    mvwprintw(application.getGame()->getPlayerWindow(), (height - 6) / 2, (width - strlen("Experience:  %d") - 2) / 2, "Experience:  %d ", m_currentExp);
    mvwprintw(application.getGame()->getPlayerWindow(), (height - 2) / 2, (width - strlen("Health:    %d/%d") - 2) / 2, "Health:    %d/%d ", m_currentHealth, m_health);
    mvwprintw(application.getGame()->getPlayerWindow(), (height + 2) / 2, (width - strlen("Energy:    %d/%d") - 2) / 2, "Energy:    %d/%d ", m_currentEnergy, m_energy);
    mvwprintw(application.getGame()->getPlayerWindow(), (height + 6) / 2, (width - strlen("Agility:     %d") - 1) / 2, "Agility:     %d ", m_agility);
    wrefresh(application.getGame()->getPlayerWindow());
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

std::shared_ptr<CCharacter> loadPlayerRogue(ifstream& is)
{
    int posX;
    is >> posX;
    int posY;
    is >> posY;
    /*int experience;
    is >> experience;
    int strenght;
    is >> strenght;*/

    std::shared_ptr<CCharacter> result;
    result.reset(new CPlayerRogue(posY, posX));
    
    return result;
}