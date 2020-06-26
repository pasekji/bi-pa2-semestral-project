#include "CCharacter.h"
#include "CApplication.h"
#include <iostream>

extern CApplication application;

CCharacter::CCharacter(int posY, int posX) : CGameObject(posY, posX)
{}

void CCharacter::rest()
{
    if(m_currentEnergy < m_energy)
        for(int i = 0; i < m_energyRegain; i++)
        {
            if(m_currentEnergy != m_energy)
                m_currentEnergy++;
        }

    return;
}

void CCharacter::takeStep()
{
    m_currentEnergy -= m_energyForStep;
}

bool CCharacter::spareEnergyToStep() const
{
    if((m_currentEnergy - m_energyForStep) >= 0)
        return true;
    else
        return false;
}

int CCharacter::getHealth() const
{
    return m_currentHealth;
}

int CCharacter::getEnergy() const
{
    return m_currentEnergy;
}

bool CCharacter::isReachable() const
{
    return m_isReachable;
}

const float CCharacter::getChanceOfBlock() const
{
    return m_chanceOfBlock;
}

bool CCharacter::isDead() const
{
    if(m_currentHealth <= 0)
        return true;
    else
        return false;
}

const attack_type CCharacter::getAttackType() const
{
    return m_attackType;
}

string CCharacter::getTypeName()
{
    return "CCharacter";
}

CGameObject* CCharacter::defaultGetTarget()
{
    int tmppos;
    CGameObject* target = nullptr;
    std::pair<int, int> pair;

    target = application.getGame()->getMap()->getTargetObject(pair = std::make_pair(tmppos = m_posY - 1, m_posX));

    if(target == nullptr)
        target = application.getGame()->getMap()->getTargetObject(pair = std::make_pair(tmppos = m_posY + 1, m_posX));        

    if(target == nullptr)
        target = application.getGame()->getMap()->getTargetObject(pair = std::make_pair(m_posY, tmppos = m_posX - 1));

    if(target == nullptr)
        target = application.getGame()->getMap()->getTargetObject(pair = std::make_pair(m_posY, tmppos = m_posX + 1));

    return target;
}

CCharacter* loadCharacter(ifstream& is)
{
    string type;
    is >> type;
    if (type == "CPlayerPaladin")
        return loadPlayerPaladin(is);
    if (type == "CPlayerRogue")
        return loadPlayerRogue(is);
    if (type == "CPlayerMage")
        return loadPlayerMage(is);
    if (type == "CEnemy")
        return loadEnemy(is);
    if (type == "neukladat")
        return nullptr;
    CCharacter* result;

    return result;
}