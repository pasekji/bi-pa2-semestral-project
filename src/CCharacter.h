#ifndef CHARACTER_H
#define CHARACTER_H

#include "CGameObject.h"
#include "enums.h"
#include "CPrimaryAttack.fwd.h"
#include <algorithm>
#include <memory>
class CCharacter : public CGameObject
{
    protected:    

        CCharacter(int posY, int posX) : CGameObject(posY, posX)
        {}
        virtual ~CCharacter() = default;

        int m_speed;
        int m_currentHealth;
        int m_health;
        int m_currentEnergy;
        int m_energy;
        int m_energyForStep;
        int m_energyRegain;
        float m_chanceOfBlock;
        attack_type m_attackType;

        void rest()
        {
            if(m_currentEnergy < m_energy)
                for(int i = 0; i < m_energyRegain; i++)
                {
                    if(m_currentEnergy != m_energy)
                        m_currentEnergy++;
                }

            return;
        }

        void takeStep()
        {
            m_currentEnergy -= m_energyForStep;
        }

        bool spareEnergyToStep() const
        {
            if((m_currentEnergy - m_energyForStep) >= 0)
                return true;
            else
                return false;
        }

        virtual bool defaultMove(int move) = 0;
        
        std::shared_ptr<CGameObject> defaultGetTarget();

    public:
        virtual int getAction() = 0;
        virtual const int getForce() const = 0;
        virtual bool interactWith() = 0;

        int getHealth()
        {
            return m_currentHealth;
        }

        virtual const float getChanceOfCriticalAttack() const = 0;

        int getEnergy()
        {
            return m_currentEnergy;
        }

        const float getChanceOfBlock() const
        {
            return m_chanceOfBlock;
        }

        bool isDead() const override
        {
            if(m_currentHealth <= 0)
                return true;
            else
                return false;
        }

        const attack_type getAttackType() const
        {
            return m_attackType;
        }

        virtual string getTypeName()
        {
            return "CCharacter";
        }
};

std::shared_ptr<CCharacter> loadCharacter(ifstream& is);

#endif