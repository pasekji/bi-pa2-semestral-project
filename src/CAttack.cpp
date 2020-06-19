#include "CAttack.h"
#include "CApplication.h"
#include <ncurses.h>

extern CApplication application;

void CAttack::visitSource(CPlayerPaladin* paladin)
{  
    paladin->getLable(m_sourceLable);
    m_attackType = paladin->getAttackType();
    m_chanceOfCritical = paladin->getChanceOfCriticalAttack();
    m_forceMax = paladin->getForce();
    m_energySource = paladin->getEnergy();

    return;
}

void CAttack::visitSource(CPlayerMage* mage)
{
    mage->getLable(m_sourceLable);
    m_attackType = mage->getAttackType();
    m_chanceOfCritical = mage->getChanceOfCriticalAttack();
    m_forceMax = mage->getForce();
    m_energySource = mage->getEnergy();    
    
    return;
}

void CAttack::visitSource(CPlayerRogue* rogue)
{
    rogue->getLable(m_sourceLable);
    m_attackType = rogue->getAttackType();
    m_chanceOfCritical = rogue->getChanceOfCriticalAttack();
    m_forceMax = rogue->getForce();
    m_energySource = rogue->getEnergy();    
    
    return;
}

void CAttack::visitSource(CEnemy* enemy)
{
    enemy->getLable(m_sourceLable);
    m_attackType = enemy->getAttackType();
    m_chanceOfCritical = 0;
    m_forceMax = enemy->getForce();
    m_energySource = enemy->getEnergy();    
    
    return;
}

void CAttack::visitTarget(CPlayerPaladin* paladin)
{  
    paladin->getLable(m_targetLable);
    m_chanceOfBlockTarget = paladin->getChanceOfBlock();
    m_healthTarget = paladin->getHealth();
    m_energyTarget = paladin->getEnergy();
        
    return;
}

void CAttack::visitTarget(CPlayerMage* mage)
{
    mage->getLable(m_targetLable);
    m_chanceOfBlockTarget = mage->getChanceOfBlock();
    m_healthTarget = mage->getHealth();
    m_energyTarget = mage->getEnergy();    
    
    return;
}

void CAttack::visitTarget(CPlayerRogue* rogue)
{
    rogue->getLable(m_targetLable);
    m_chanceOfBlockTarget = rogue->getChanceOfBlock();
    m_healthTarget = rogue->getHealth();
    m_energyTarget = rogue->getEnergy();    
    
    return;
}

void CAttack::visitTarget(CEnemy* enemy)
{
    enemy->getLable(m_targetLable);
    m_chanceOfBlockTarget = enemy->getChanceOfBlock();
    m_healthTarget = enemy->getHealth();
    m_energyTarget = enemy->getEnergy();     
    
    return;
}