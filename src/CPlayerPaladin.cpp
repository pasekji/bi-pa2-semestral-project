#include "CPlayerPaladin.h"
#include "CApplication.h"
#include "CPrimaryAttack.h"
#include "CPickup.h"


extern CApplication application;

CPlayerPaladin::CPlayerPaladin(int posY, int posX) : CPlayer(posY, posX)
{
    m_sharedDerived = std::dynamic_pointer_cast<CPlayerPaladin> (m_sharedThis);
    halfdelay(1);
    m_inventorySize = 20;
    m_speed = 1;
    m_health = 100;
    m_currentHealth = m_health;
    m_energy = 75;
    m_currentEnergy = m_energy;
    m_strength = 10;
    m_energyForStep = 2;
    m_energyRegain = 3;
    m_primaryAttackType = SLASH;
    m_inventory.reset(new CInventory(m_inventorySize));
}

int CPlayerPaladin::getAction()
{
    defaultStep(m_move);                  // sprint is not availiable with paladin

    if(!isDead())
    {
        if(toupper(m_move) == 'C')
            slowTime(m_move);
        if(!defaultMove(m_move))
            if(!interactWith())
                rest();
    }
    return m_move;
}

bool CPlayerPaladin::interactWith()
{
    bool used = false;

    std::shared_ptr<CGameObject> target = directionGetTarget();

    if(target == nullptr)
        return used;
        
    switch (m_move)
    {
        case 'E':
        case 'e':
            if(m_currentEnergy >= m_strength)
                paladinPrimaryAttack(target);
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

bool CPlayerPaladin::paladinPrimaryAttack(std::shared_ptr<CGameObject> target)
{
    std::shared_ptr<CAttack> attack;
    attack = (new CPrimaryAttack(m_sharedDerived, target, m_primaryAttackType))->getPtr();
    application.getGame()->pushEvent(attack);
    return true;
}

void CPlayerPaladin::showStats() const
{
    int height, width;
    getmaxyx(application.getGame()->getPlayerWindow(), height, width);
    mvwprintw(application.getGame()->getPlayerWindow(), (height - 14) / 2, (width - strlen("PLAYER")) / 2, "PLAYER ");
    mvwprintw(application.getGame()->getPlayerWindow(), (height - 10) / 2, (width - strlen("Class:     PALADIN")) / 2, "Class:     PALADIN ");
    mvwprintw(application.getGame()->getPlayerWindow(), (height - 6) / 2, (width - strlen("Experience:  %d") - 2) / 2, "Experience:  %d ", m_currentExp);
    mvwprintw(application.getGame()->getPlayerWindow(), (height - 2) / 2, (width - strlen("Health:    %d/%d") - 2) / 2, "Health:    %d/%d ", m_currentHealth, m_health);
    mvwprintw(application.getGame()->getPlayerWindow(), (height + 2) / 2, (width - strlen("Energy:    %d/%d") - 2) / 2, "Energy:    %d/%d ", m_currentEnergy, m_energy);
    mvwprintw(application.getGame()->getPlayerWindow(), (height + 6) / 2, (width - strlen("Strength:     %d") - 1) / 2, "Strength:     %d ", m_strength);

    wrefresh(application.getGame()->getPlayerWindow());
    return;
}

void CPlayerPaladin::slowTime(int& move)
{    
    while(toupper(move) == 'C')
        defaultStep(move);
    changeForm('^');
}

bool CPlayerPaladin::updateSource(std::shared_ptr<CPickup> pickup)
{
    pickup->updateSource(m_sharedDerived);
    return true;
}

bool CPlayerPaladin::acceptSource(std::shared_ptr<CPickup> pickup)
{
    pickup->visitSource(m_sharedDerived);
    return true;
}

bool CPlayerPaladin::acceptTarget(std::shared_ptr<CPickup> pickup)
{
    return false;
}

std::shared_ptr<CCharacter> loadPlayerPaladin(ifstream& is)
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
    result.reset(new CPlayerPaladin(posY, posX));
    
    return result;
}