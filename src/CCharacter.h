#ifndef CHARACTER_H
#define CHARACTER_H

#include "CGameObject.h"
#include "enums.h"
#include "CPrimaryAttack.fwd.h"
#include <algorithm>
#include <memory>
class CCharacter : public CGameObject
{
    public:
        virtual int getAction() = 0;
        virtual const int getForce() const = 0;
        virtual bool interactWith() = 0;

        int getHealth() const;

        virtual const float getChanceOfCriticalAttack() const = 0;

        int getEnergy() const;

        const float getChanceOfBlock() const;

        bool isDead() const override;

        const attack_type getAttackType() const;

        virtual string getTypeName();

        bool isReachable() const;

        virtual ~CCharacter() = default;
        
    protected:    

        CCharacter(int posY, int posX);
        bool m_isReachable = true;
        int m_speed;
        int m_currentHealth;
        int m_health;
        int m_currentEnergy;
        int m_energy;
        int m_energyForStep;
        int m_energyRegain;
        float m_chanceOfBlock;
        attack_type m_attackType;

        void rest();

        void takeStep();

        bool spareEnergyToStep() const;

        virtual bool defaultMove(int move) = 0;
        
        CGameObject* defaultGetTarget();

};

CCharacter* loadCharacter(ifstream& is);

#endif