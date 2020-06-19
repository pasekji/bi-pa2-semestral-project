#include "CPrimaryAttack.h"
#include "CApplication.h"

extern CApplication application;

CPrimaryAttack::CPrimaryAttack(CGameObject* source, CGameObject* target, attack_type attackType) : CAttack(source, target, attackType)
{
    source->acceptSource(this);
    if(!target->acceptTarget(this))
        m_canAttack = false;
    else
        m_canAttack = true;

    evaluateAttack();
}

CPrimaryAttack::~CPrimaryAttack()
{

}

void CPrimaryAttack::print() const
{
    return;
}

void CPrimaryAttack::evaluateAttack()       // na secondary attack lze pouzit jinou distrubuci
{
    if(m_canAttack)
    {
        std::default_random_engine randomGenerator(rand());
        std::uniform_int_distribution<int> forceRoll(1, m_forceMax);
        std::uniform_real_distribution<float> criticalRoll(0.0f, 1.0f);
        std::uniform_real_distribution<float> blockRoll(0.0f, 1.0f);
        m_forceMax = forceRoll(randomGenerator);
        m_forceGiven = m_energySource % m_forceMax;
        if(m_forceGiven == 0)
            m_hit = false;
        m_energyLostSource = m_forceGiven;
        if( criticalRoll(randomGenerator) <= m_chanceOfCritical)
        {
            
        }
        


    }
    
    return;
}

void CPrimaryAttack::updateObjects()
{
    return;
}