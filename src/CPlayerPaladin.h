#ifndef PALADIN_H
#define PALADIN_H

#include "CPlayer.h"
#include "CPrimaryAttack.fwd.h"
#include "CPlayerPaladin.fwd.h"
#include "CAttack.fwd.h"


class CPlayerPaladin : public CPlayer
{  
    public:
        int getAction() override;
        void showStats() const override;
        CPlayerPaladin(WINDOW* objectSpace, int posY, int posX);
        ~CPlayerPaladin()
        {}

        const int getForce() const override
        {
            return m_strength;
        }

        const float getChanceOfCriticalAttack() const override
        {
            return m_chanceOfCriticalAttack;
        }

        void save(ofstream& os) override
        {
            os << getTypeName() << endl;
        }

        virtual string getTypeName()
        {
            return "CPlayerPaladin";
        }

        bool updateSource(CPickup* pickup) override;
        bool acceptSource(CPickup* pickup) override;
        bool acceptTarget(CPickup* pickup) override;

        friend class CAttack;
        friend class CPickup;

    private:
        bool interactWith() override;
        int m_strength;
        float m_chanceOfCriticalAttack;
        attack_type m_primaryAttackType;
        bool paladinPrimaryAttack(CGameObject* target);
        bool paladinSpecialAbility();                       // knockout the enemy for x rounds ?? 

};

#endif