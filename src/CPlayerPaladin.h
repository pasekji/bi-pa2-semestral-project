#ifndef PALADIN_H
#define PALADIN_H

#include "CPlayer.h"


class CPlayerPaladin : public CPlayer
{  
    public:
        int getAction() override;
        bool interactWith() override;
        bool accept(CAttack* attack) override;
        void showStats() const override;
        CPlayerPaladin(WINDOW* objectSpace, int posY, int posX);
        ~CPlayerPaladin()
        {}

    private:
        int m_strength;
        float m_chanceOfCriticalAttack;
        attack_type m_primaryAttackType;
        bool paladinPrimaryAttack(CGameObject* target);
        bool paladinSpecialAbility();                       // knockout the enemy for x rounds ?? 

};

#endif