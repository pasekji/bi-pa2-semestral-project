#ifndef CHARACTER_H
#define CHARACTER_H

#include "CGameObject.h"
#include "enums.h"
#include <algorithm>
class CCharacter : public CGameObject
{
    protected:    

        CCharacter(WINDOW* objectSpace, int posY, int posX) : CGameObject(objectSpace, posY, posX)
        {}
        ~CCharacter(){}

        int m_speed;
        int m_currentHealth;
        int m_health;
        int m_currentEnergy;
        int m_energy;
        int m_energyForStep;
        int m_energyRegain;
        float m_chanceOfBlock;
        attack_type m_attackType;

        virtual void die() = 0;

        virtual void rest()
        {
            if(m_currentEnergy < m_energy)
                for(int i = 0; i < m_energyRegain; i++)
                {
                    if(m_currentEnergy != m_energy)
                        m_currentEnergy++;
                }

            return;
        }

        virtual void takeStep()
        {
            m_currentEnergy -= m_energyForStep;
        }

        virtual bool spareEnergyToStep() const
        {
            if((m_currentEnergy - m_energyForStep) >= 0)
                return true;
            else
                return false;
        } 

        virtual bool defaultMove(int move) = 0;

        virtual CGameObject* fetchTarget() const
        {
            return nullptr;
        }

    public:
        virtual int getAction() = 0;
        virtual const int getForce() const = 0;
        virtual bool interactWith() = 0;

        int & getHealth()
        {
            return m_currentHealth;
        }

        int & getEnergy()
        {
            return m_currentEnergy;
        }

        const float getChanceOfBlock() const
        {
            return m_chanceOfBlock;
        }

        bool isDead() const
        {
            if(m_currentHealth <= 0)
                return true;
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

#endif