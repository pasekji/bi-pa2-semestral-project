#include "CPlayerPaladin.h"
#include "CApplication.h"
#include "CPrimaryAttack.h"


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
    m_primaryAttackType = SLAIN;
    m_inventory = new CInventory(m_inventorySize);
}

int CPlayerPaladin::getAction()
{
    defaultStep(m_move);                  // sprint is not availiable with paladin
    
    if(!defaultMove(m_move))
        if(!interactWith())
            rest();
  
    return m_move;
}

bool CPlayerPaladin::interactWith()
{
    int tmppos;
    bool used = false;
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
        return used;
        
    switch (this->m_move)
    {
        case 'E':
        case 'e':
            paladinPrimaryAttack(target);
            used = true;
            break;

        case 'G':
        case 'g':
            used = true;
            break;

        default:
            break;
    }

    return used;
}

bool CPlayerPaladin::acceptSource(CAttack* attack)
{
    attack->visitSource(this);
    return true;
}

bool CPlayerPaladin::acceptTarget(CAttack* attack)
{
    attack->visitTarget(this);
    return true;
}

bool CPlayerPaladin::paladinPrimaryAttack(CGameObject* target)
{
    m_attackType = m_primaryAttackType;
    CAttack* attack = new CPrimaryAttack(this, target, SLAIN);
    return true;
}

void CPlayerPaladin::showStats() const
{
    int height, width;
    getmaxyx(application.getGame().getPlayerWindow(), height, width);

    mvwprintw(application.getGame().getPlayerWindow(), (height - 14) / 2, (width - strlen("PLAYER")) / 2, "PLAYER");
    mvwprintw(application.getGame().getPlayerWindow(), (height - 10) / 2, (width - strlen("Level:   %d") - 1) / 2, "Level:   %d", m_level);
    mvwprintw(application.getGame().getPlayerWindow(), (height - 6) / 2, (width - strlen("Name:   %s") - m_playerName.length()) / 2, "Name:     %s", m_playerName.c_str());
    mvwprintw(application.getGame().getPlayerWindow(), (height - 2) / 2, (width - strlen("Class:     PALADIN")) / 2, "Class:     PALADIN");
    mvwprintw(application.getGame().getPlayerWindow(), (height + 2) / 2, (width - strlen("Experience:  %d/%d") - 2) / 2, "Experience:  %d/%d", m_currentExp, m_expTarget);
    mvwprintw(application.getGame().getPlayerWindow(), (height + 6) / 2, (width - strlen("Health:    %d/%d") - 2) / 2, "Health:    %d/%d", m_currentHealth, m_health);
    mvwprintw(application.getGame().getPlayerWindow(), (height + 10) / 2, (width - strlen("Energy:    %d/%d") - 2) / 2, "Energy:    %d/%d", m_currentEnergy, m_energy);
    mvwprintw(application.getGame().getPlayerWindow(), (height + 14) / 2, (width - strlen("Strength:     %d") - 1) / 2, "Strength:     %d", m_strength);

    wrefresh(application.getGame().getPlayerWindow());
    return;
}