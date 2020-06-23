#ifndef ROGUE_H
#define ROGUE_H

#include "CPlayer.h"
#include "CPrimaryAttack.fwd.h"
#include "CAttack.fwd.h"
#include "CPlayerRogue.fwd.h"


class CPlayerRogue : public CPlayer
{
    public:
        int getAction() override;
        bool interactWith() override;
        void showStats() const override;
        CPlayerRogue(WINDOW* objectSpace, int posY, int posX);

        ~CPlayerRogue()
        {}

        const int getForce() const override
        {
            return m_agility;
        }

        const float getChanceOfCriticalAttack() const override
        {
            return m_chanceOfDoubleHit;
        }

        virtual string getTypeName()
        {
            return "CPlayerRogue";
        }

        void save(ofstream& os) override
        {
            os << getTypeName() << endl;
        }

        bool updateSource(CPickup* pickup) override;
        bool acceptSource(CPickup* pickup) override;
        bool acceptTarget(CPickup* pickup) override;

        friend class CAttack;
        friend class CPickup;

    private:
        int m_agility;
        float m_chanceOfDoubleHit;
        attack_type m_primaryAttackType;
        bool roguePrimaryAttack();
        void rogueSpecialAbility();     // jump over x spaces in direction of player
};

#endif