#ifndef MAGE_H
#define MAGE_H

#include "CPlayer.h"
#include "CPrimaryAttack.fwd.h"
#include "CAttack.fwd.h"
#include "CPlayerMage.fwd.h"

class CPlayerMage : public CPlayer
{  
    public:
        int getAction() override;
        bool interactWith() override;
        void showStats() const override;
        CPlayerMage(WINDOW* objectSpace, int posY, int posX);

        ~CPlayerMage()
        {}

        const int getForce() const override
        {
            return m_wisdom;
        }

        const float getChanceOfCriticalAttack() const override
        {
            return m_chanceOfCriticalAttack;
        }

        virtual string getTypeName()
        {
            return "CPlayerMage";
        }

        void save(ofstream& os) override
        {
            os << getTypeName();
            os << m_posX;
            os << m_posY;
            os << endl;
        }

        bool updateSource(CPickup* pickup) override;
        bool acceptSource(CPickup* pickup) override;
        bool acceptTarget(CPickup* pickup) override;
        
        friend class CAttack;
        friend class CPickup;

    private:
        int m_wisdom;
        float m_chanceOfCriticalAttack;
        attack_type m_primaryAttackType;
        attack_type m_secondaryAttackType;
        bool magePrimaryAttack();
        bool mageSecondaryAttack();
        bool mageSpecialAbility();
};

CGameObject* loadPlayerMage(ifstream& is, WINDOW* objectSpace);

#endif