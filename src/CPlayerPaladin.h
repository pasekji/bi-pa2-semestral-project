#ifndef PALADIN_H
#define PALADIN_H

#include "CPlayer.h"


class CPlayerPaladin : public CPlayer
{  
    public:
        int getAction() override;
        bool acceptSource(CAttack* attack) override;
        bool acceptTarget(CAttack* attack) override;
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
            writeString(os, getTypeName());
        }

        virtual string getTypeName()
        {
            return "CPlayerPaladin";
        }

    private:
        bool interactWith() override;
        int m_strength;
        float m_chanceOfCriticalAttack;
        attack_type m_primaryAttackType;
        bool paladinPrimaryAttack(CGameObject* target);
        bool paladinSpecialAbility();                       // knockout the enemy for x rounds ?? 

};

#endif