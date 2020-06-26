#include "CAttack.h"
#include "CApplication.h"
#include <ncurses.h>

extern CApplication application;


CAttack::CAttack(std::shared_ptr<CGameObject> source, std::shared_ptr<CGameObject> target, attack_type attackType) : CEvent(source, target)
{
    m_attackType = attackType;
    m_chanceOfCritical = 0;
}

void CAttack::visitSource(std::shared_ptr<CPlayer> player)
{  
    player->getLabel(m_sourceLabel);
    m_chanceOfCritical = player->getChanceOfCriticalAttack();
    m_forceMax = player->getForce();
    m_energySource = player->getEnergy();

    return;
}

void CAttack::visitSource(std::shared_ptr<CEnemy> enemy)
{
    enemy->getLabel(m_sourceLabel);
    m_chanceOfCritical = enemy->getChanceOfCriticalAttack() / 3;
    m_forceMax = enemy->getForce();
    m_energySource = enemy->getEnergy();    
    
    return;
}

void CAttack::visitTarget(std::shared_ptr<CPlayer> player)
{
    player->getLabel(m_targetLabel);
    m_targetReachable = player->isReachable();
    m_chanceOfBlockTarget = player->getChanceOfBlock();
    m_healthTarget = player->getHealth();
    m_energyTarget = player->getEnergy();
        
    return;
}

void CAttack::visitTarget(std::shared_ptr<CEnemy> enemy)
{
    enemy->getLabel(m_targetLabel);
    m_targetReachable = enemy->isReachable();
    m_chanceOfBlockTarget = enemy->getChanceOfBlock();
    m_healthTarget = enemy->getHealth();
    m_energyTarget = enemy->getEnergy();     
    
    return;
}

void CAttack::updateSource(std::shared_ptr<CPlayer> player)
{
    player->m_currentEnergy -= m_energyLostSource;
    player->m_currentExp += m_expGain;

    return;
}

void CAttack::updateSource(std::shared_ptr<CEnemy> enemy)
{
    enemy->m_currentEnergy -= m_energyLostSource;
    enemy->m_triggerAttack = false;

    return;
}

void CAttack::updateTarget(std::shared_ptr<CPlayer> player)
{
    player->m_currentHealth -= m_healthLostTarget;
    player->m_currentEnergy -= m_energyLostTarget;

    return;
}

void CAttack::updateTarget(std::shared_ptr<CEnemy> enemy)
{
    enemy->m_currentHealth -= m_healthLostTarget;
    enemy->m_currentEnergy -= m_energyLostTarget;
    enemy->m_triggerAttack = true;

    return;
}