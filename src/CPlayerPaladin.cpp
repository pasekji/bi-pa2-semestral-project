#include "CPlayerPaladin.h"
#include "CApplication.h"
#include "CPrimaryAttack.h"
#include "CPickup.h"


extern CApplication application;

CPlayerPaladin::CPlayerPaladin(WINDOW* objectSpace, int posY, int posX) : CPlayer(objectSpace, posY, posX)
{
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
    m_inventory = new CInventory(m_inventorySize);
}

int CPlayerPaladin::getAction()
{
    defaultStep(m_move);                  // sprint is not availiable with paladin

    if(!isDead())
        if(!defaultMove(m_move))
            if(!interactWith())
                rest();
  
    return m_move;
}

bool CPlayerPaladin::interactWith()
{
    bool used = false;

    CGameObject* target = directionGetTarget();

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

        case 'G':
        case 'g':
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

bool CPlayerPaladin::paladinPrimaryAttack(CGameObject* target)
{
    CAttack* attack = new CPrimaryAttack(this, target, m_primaryAttackType);
    if(attack != nullptr) return true;
    return false;
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

bool CPlayerPaladin::updateSource(CPickup* pickup)
{
    pickup->updateSource(this);
    return true;
}

bool CPlayerPaladin::acceptSource(CPickup* pickup)
{
    pickup->visitSource(this);
    return true;
}

bool CPlayerPaladin::acceptTarget(CPickup* pickup)
{
    return false;
}
